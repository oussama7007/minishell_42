/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/13 01:49:04 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

static int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (1);
	}
	return (0);
}

static int	handle_directory_command(char *cmd_arg)
{
	if (is_directory(cmd_arg))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_arg, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
	return (0);
}

static void	validate_and_execute(t_command *cmd, char **env)
{
	char	*cmd_path;

	cmd_path = find_executable_path(cmd->args[0], env);
	if (!cmd_path)
	{
		handle_command_not_found(cmd->args[0]);
		exit(127);
	}
	execute_child_process(cmd_path, cmd->args, env);
}

void	child_process_logic(t_command *cmd, char ***env)
{
	int	builtin_status;
	int	dir_status;

	if (!handle_redirection_child(cmd))
		exit(1);
	if (!cmd->cmd)
		exit(0);
	dir_status = handle_directory_command(cmd->args[0]);
	if (dir_status != 0)
		exit(dir_status);
	builtin_status = is_built_ins(cmd->args, env);
	if (builtin_status != 999)
		exit(builtin_status);
	validate_and_execute(cmd, *env);
}
