/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:16:56 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/21 17:17:45 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

void	setup_child_io(int prev_pipe, int *pipe_fds, t_command *cmd)
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

void	execute_single_cmd(t_command *cmd, char **envp)
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
