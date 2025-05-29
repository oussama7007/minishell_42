/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:44:44 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/28 17:45:17 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"


// Forward declaration for the function that executes a single command logic
// This function would be your refactored single command executor from execute_heart.c
// It needs to handle builtins or prepare for execve if external.
// It's crucial that if it's an external command, and it's in a pipe's child, it directly execve's.
// If it's a standalone external command, it might do its own fork (like your current ft_execute_external).
// For this pipeline, it will be called with is_in_pipe_child = 1.
int	run_single_command_logic(t_command *cmd_node, char ***env_ptr, \
								int is_in_pipe_child);

// Helper to print error, and return value (norm-friendly for error paths)
static int	perror_ret_val(const char *msg_prefix, int ret_val)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)msg_prefix, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (ret_val);
}

// Helper to print error and exit (for child processes)
static void	perror_exit_child(const char *msg_prefix, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)msg_prefix, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(exit_code);
}

// Helper to count commands in a potential pipeline
static int	count_pipeline_commands(t_command *cmd_list)
{
	int	count;

	count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}

// Sets up command-specific file IO redirections (<, >, >>)
// This is called *after* pipe FDs are set up for stdin/stdout,
// so these file redirections can override the pipe.
static int	setup_cmd_file_redirections(t_command *cmd)
{
	int	fd;
	// This is a simplified version. Your actual t_command might have arrays for red_in/red_out.
	// You'll need to iterate and handle the last one of each type, or all if appropriate.
	// Also, heredoc (<<) needs special handling (reading input, temp file).

	if (cmd->red_in && cmd->red_in[0]) // Handles '<'
	{
		fd = open(cmd->red_in[0], O_RDONLY);
		if (fd == -1)
			return (perror_ret_val(cmd->red_in[0], 1));
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (perror_ret_val("dup2 for < redirection", 1));
		}
		close(fd);
	}
	// Add heredoc handling here if cmd->heredoc_delimiter exists

	if (cmd->red_out && cmd->red_out[0]) // Handles '>' and '>>'
	{
		int	flags;
		// Assuming cmd->append is an array corresponding to cmd->red_out
		if (cmd->append && cmd->append[0]) // Check append flag for this redirection
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(cmd->red_out[0], flags, 0644);
		if (fd == -1)
			return (perror_ret_val(cmd->red_out[0], 1));
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			return (perror_ret_val("dup2 for >/>> redirection", 1));
		}
		close(fd);
	}
	return (0);
}

// This function is executed by the child process for each command in the pipeline
static void	child_process_exec(t_command *cmd, char ***env_ptr, \
								int read_from_fd, int write_to_fd, \
								int next_cmd_pipe_read_end)
{
	int	status;

	if (read_from_fd != STDIN_FILENO)
	{
		if (dup2(read_from_fd, STDIN_FILENO) == -1)
			perror_exit_child("dup2 stdin for pipe", 1);
		close(read_from_fd);
	}
	if (write_to_fd != STDOUT_FILENO)
	{
		if (dup2(write_to_fd, STDOUT_FILENO) == -1)
			perror_exit_child("dup2 stdout for pipe", 1);
		close(write_to_fd);
	}
	if (next_cmd_pipe_read_end != -1) // Child closes read-end of its output pipe
		close(next_cmd_pipe_read_end);
	if (setup_cmd_file_redirections(cmd) != 0) // Apply cmd-specific redirects
		exit(1); // Redirection error, child exits
	status = run_single_command_logic(cmd, env_ptr, 1); // 1 = is_in_pipe_child
	exit(status);
}

// Sets up pipe, forks, and calls child_process_exec. Manages FDs in parent.
static int	launch_piped_command(t_command *cmd, char ***env_ptr, \
								int *prev_read_fd, pid_t *child_pid)
{
	int	pipe_fds[2];
	int	write_to_fd;
	int	next_cmd_read_end_for_child; // Read end of pipe child writes to

	pipe_fds[0] = -1; // Initialize to suppress maybe-uninitialized warning
	pipe_fds[1] = -1;
	next_cmd_read_end_for_child = -1;
	if (cmd->next) // If not the last command, create a pipe for its output
	{
		if (pipe(pipe_fds) == -1)
			return (perror_ret_val("pipe", 1));
		write_to_fd = pipe_fds[1];
		next_cmd_read_end_for_child = pipe_fds[0];
	}
	else
		write_to_fd = STDOUT_FILENO;
	*child_pid = fork();
	if (*child_pid == -1)
	{
		if (cmd->next)
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
		}
		return (perror_ret_val("fork", 1));
	}
	if (*child_pid == 0) // Child process
		child_process_exec(cmd, env_ptr, *prev_read_fd, \
							write_to_fd, next_cmd_read_end_for_child);
	// Parent process:
	if (*prev_read_fd != STDIN_FILENO)
		close(*prev_read_fd);
	if (cmd->next)
	{
		close(write_to_fd); // Parent closes write end of the current pipe
		*prev_read_fd = pipe_fds[0]; // Save read end for the next command
	}
	return (0); // Success
}

// Waits for all child processes in the pipeline and returns last command's status
static int	wait_for_pipeline(pid_t *pids, int num_cmds)
{
	int	i;
	int	status;
	int	last_cmd_status;

	i = 0;
	last_cmd_status = 0;
	while (i < num_cmds)
	{
		if (waitpid(pids[i], &status, 0) == -1 && errno != ECHILD)
			perror_ret_val("waitpid", 1); // Log error but continue waiting
		if (i == num_cmds - 1) // Status of the last command
		{
			if (WIFEXITED(status))
				last_cmd_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_cmd_status = 128 + WTERMSIG(status);
			else
				last_cmd_status = status; // Fallback, less precise
		}
		i++;
	}
	free(pids);
	return (last_cmd_status);
}

// Main function to execute a pipeline
int	execute_pipeline(t_command *cmd_list, char ***env_ptr)
{
	t_command	*current_cmd;
	pid_t		*pids;
	int			num_cmds;
	int			i;
	int			prev_pipe_read_fd;

	num_cmds = count_pipeline_commands(cmd_list);
	// This function is specifically for pipelines (num_cmds > 1)
	// Single commands are handled by run_single_command_logic directly.
	if (num_cmds <= 1) // Should be caught by caller, but defensive
		return (run_single_command_logic(cmd_list, env_ptr, 0));
	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pids)
		return (perror_ret_val("malloc for pids", 1));
	prev_pipe_read_fd = STDIN_FILENO;
	current_cmd = cmd_list;
	i = 0;
	while (i < num_cmds) // Use num_cmds for loop bound
	{
		if (launch_piped_command(current_cmd, env_ptr, \
									&prev_pipe_read_fd, &pids[i]) != 0)
		{
			// Error launching, cleanup previously forked, free pids
			int k = 0;
			while(k < i) { waitpid(pids[k], NULL, 0); k++;}
			free(pids);
			if (prev_pipe_read_fd != STDIN_FILENO) close(prev_pipe_read_fd);
			return (1); // General error
		}
		current_cmd = current_cmd->next;
		i++;
	}
	// Close the read end of the last pipe segment in the parent, if any
	if (prev_pipe_read_fd != STDIN_FILENO)
		close(prev_pipe_read_fd);
	return (wait_for_pipeline(pids, num_cmds));
}
