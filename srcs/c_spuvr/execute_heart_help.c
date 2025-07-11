/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heart_help.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:32:54 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/11 22:33:31 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"
#include <sys/stat.h>

static int	execute_single_command(t_command *cmd, char ***env_ptr)
{
	pid_t	pid;
	int		status;

	if (cmd->cmd && is_parent_only_builtin(cmd->cmd)
		&& !has_redirection(cmd))
		return (is_built_ins(cmd->args, env_ptr));
	pid = fork();
	if (pid == -1)
		return (handle_fork_error(NULL));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process_logic(cmd, env_ptr);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	status = wait_for_child(pid);
	setup_signal_handlers();
	return (status);
}

int	ft_execute_command_list(t_command *cmd_list, t_token *tokens,
			char ***env_ptr, t_data *data)
{
	t_exit_data	exit_data;

	if (!cmd_list)
		return (0);
	if (cmd_list->cmd
		&& ft_strcmp(cmd_list->cmd, "exit") == 0 && !cmd_list->next)
	{
		exit_data.env_ptr = env_ptr;
		exit_data.commands = cmd_list;
		exit_data.tokens = tokens;
		exit_data.data = data;
		return (ft_exit(cmd_list->args, &exit_data));
	}
	if (cmd_list->next)
		return (execute_pipeline(cmd_list, env_ptr, data));
	return (execute_single_command(cmd_list, env_ptr));
}
