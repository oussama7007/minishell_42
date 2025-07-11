/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:44:44 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/11 02:48:32 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static void	execute_child(t_command *cmd, char ***env_ptr,
		int prev_pipe, int *pipe_fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_io(prev_pipe, pipe_fd, cmd);
	child_process_logic(cmd, env_ptr);
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

static int	wait_for_all_children(pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	wpid;

	last_status = 1;
	wpid = 0;
	while (wpid != -1)
	{
		wpid = wait(&status);
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
	}
	return (last_status);
}

static pid_t	pipeline_loop(t_command *cmd, char ***env_ptr, int *prev_pipe)
{
	pid_t	pid;
	pid_t	last_pid;
	int		pipe_fds[2];

	last_pid = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fds) == -1)
		{
			perror("minishell: pipe");
			return (-2);
		}
		pid = fork();
		if (pid < 0)
			return (perror("minishell: fork"), -1);
		if (pid == 0)
			execute_child(cmd, env_ptr, *prev_pipe, pipe_fds);
		last_pid = pid;
		handle_parent_pipes(prev_pipe, pipe_fds, cmd);
		cmd = cmd->next;
	}
	return (last_pid);
}

int	execute_pipeline(t_command *commands, char ***env_ptr, t_data *data)
{
	int		prev_pipe;
	pid_t	last_pid;
	int		final_status;

	(void)data;
	prev_pipe = STDIN_FILENO;
	signal(SIGINT, sigint_handler_exec);
	last_pid = pipeline_loop(commands, env_ptr, &prev_pipe);
	if (last_pid < 0)
	{
		if (last_pid == -1)
			wait_for_all_children(0);
		return (1);
	}
	final_status = wait_for_all_children(last_pid);
	setup_signal_handlers();
	return (final_status);
}
