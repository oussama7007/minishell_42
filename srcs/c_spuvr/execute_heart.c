/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/22 18:26:53 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

static int	ft_execute_external(t_command *cmd, char **envp)
{
	char	*cmd_path;
	pid_t	pid;
	int	 	status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	cmd_path = find_executable_path(cmd->args[0], envp);
	if (!cmd_path)
		return (handle_command_not_found(cmd->args[0]));
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (1);
	}
	if (pid == 0)
		execute_child_process(cmd_path, cmd->args, envp);
	free(cmd_path);
	status = wait_for_child(pid);
	return (status);
}

int	ft_execute_command_list(t_command *cmd_list, char ***env_ptr)
{
	int	status;
	int	builtin_status;

	if (!cmd_list || !cmd_list->args || !cmd_list->args[0])
		return (0);
	builtin_status = is_built_ins(cmd_list->args, env_ptr);
	if (builtin_status == 999)
		status = ft_execute_external(cmd_list, *env_ptr);
	else
		status = builtin_status;
	return (status);
}
