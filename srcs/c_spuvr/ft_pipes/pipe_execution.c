/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:44:44 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/11 02:33:13 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static void	execute_child(t_command *cmd, char ***env_ptr,
			int prev, int *pipe_fd)
{
	setup_child_io(prev, pipe_fd, cmd);
	setup_child_signals(cmd);
	handle_redirection_child(cmd);
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

static int	wait_for_pipeline(pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
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
		pid = waitpid(-1, &status, 0);
	}
	return (last_status);
}

int	execute_pipeline(t_command *commands, char ***env_ptr, t_data *data)
{
	int			pipe_fds[2];
	int			prev_pipe;
	pid_t		pid;
	pid_t		last_pid;
	t_command	*cmd;
	int			last_status;

	prev_pipe = STDIN_FILENO;
	cmd = commands;
	last_pid = -1;
	signal(SIGINT, sigint_handler_exec);
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fds) == -1)
			return (1);
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork");
			if (prev_pipe != STDIN_FILENO)
				close(prev_pipe);
			if (cmd->next)
			{
				close(pipe_fds[0]);
				close(pipe_fds[1]);
			}
			return (1);
		}
		if (pid == 0)
			execute_child(cmd, env_ptr, prev_pipe, pipe_fds);
		last_pid = pid;
		handle_parent_pipes(&prev_pipe, pipe_fds, cmd);
		cmd = cmd->next;
	}
	last_status = wait_for_pipeline(last_pid);
	setup_signal_handlers();
	return (last_status);
}
