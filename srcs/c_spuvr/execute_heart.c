/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/21 04:15:31 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"
#include <sys/stat.h>

static int	is_directory(const char *path)
{
	struct stat path_stat;

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
		ft_putstr_fd(": is a directory\n", 2);
		return (999);
	}
	return (0);
}

static int	handle_cmd_path_error(char *cmd_arg)
{
	int	saved_errno;
    
	saved_errno = errno;
	if (is_direct_path(cmd_arg))
		return (ft_print_exec_error(cmd_arg, saved_errno));
	else
		return (handle_command_not_found(cmd_arg));
}

static int	ft_execute_external(t_command *cmd, char **envp)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;
	int	dir_status;

	if (!cmd || !cmd->args || !cmd->args[0] || !cmd->args[0][0])
		return (1);
	dir_status = handle_directory_command(cmd->args[0]);
	if (dir_status == 999)
		return (126);
	cmd_path = find_executable_path(cmd->args[0], envp);
	if (!cmd_path)
		return (handle_cmd_path_error(cmd->args[0]));
	pid = fork();
	if (pid == -1)
		return (handle_fork_error(cmd_path));
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
	if (cmd_list->next)
		return (execute_pipeline(cmd_list, env_ptr));
	builtin_status = is_built_ins(cmd_list->args, env_ptr);
	if (builtin_status == 999)
		status = ft_execute_external(cmd_list, *env_ptr);
	else
		status = builtin_status;
	return (status);
}
