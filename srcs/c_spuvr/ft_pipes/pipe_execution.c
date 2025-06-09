/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:44:44 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/09 12:45:28 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static void	setup_child_io(int prev_pipe, int *pipe_fds, t_command *cmd)
{
	if (prev_pipe != STDIN_FILENO)
	{
		if (dup2(prev_pipe, STDIN_FILENO) == -1)
			exit(1);
		close(prev_pipe);
	}
	if (cmd->next)
	{
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipe_fds[1]);
		close(pipe_fds[0]);
	}
}

static void	execute_single_cmd(t_command *cmd, char **envp)
{
	char	*cmd_path;
	int		builtin_status;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(0);
	builtin_status = is_built_ins(cmd->args, &envp);
	if (builtin_status != 999)
		exit(builtin_status);
	cmd_path = find_executable_path(cmd->args[0], envp);
	if (!cmd_path)
	{
		handle_command_not_found(cmd->args[0]);
		exit(127);
	}
	execute_child_process(cmd_path, cmd->args, envp);
}

static void	execute_child(t_command *cmd, char ***env_ptr, int prev, int *pipe_fd)
{
	setup_child_io(prev, pipe_fd, cmd);
	setup_child_signals();
	handle_redirection_child(cmd);
	execute_single_cmd(cmd, *env_ptr);
}

static void	handle_parent_pipes(int *prev_pipe, int *pipe_fds, t_command *cmd)
{
	if (*prev_pipe != STDIN_FILENO)
		close(*prev_pipe);
	if (cmd->next)
	{
		close(pipe_fds[1]);
		*prev_pipe = pipe_fds[0];
	}
}

static int	wait_for_pipeline(pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
			else
				last_status = 1;
		}
	}
	return (last_status);
}

int	execute_pipeline(t_command *commands, char ***env_ptr)
{
	int			pipe_fds[2];
	int			prev_pipe;
	pid_t		pid;
	pid_t		last_pid;
	t_command	*cmd;

	prev_pipe = STDIN_FILENO;
	cmd = commands;
	last_pid = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fds) == -1)
			return (1);
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			execute_child(cmd, env_ptr, prev_pipe, pipe_fds);
		last_pid = pid;
		handle_parent_pipes(&prev_pipe, pipe_fds, cmd);
		cmd = cmd->next;
	}
	return (wait_for_pipeline(last_pid));
}
