/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/28 21:49:39 by oait-si-         ###   ########.fr       */
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

static void	child_process_logic(t_command *cmd, char ***env, int heredoc_fd)
{
	int		builtin_status;
	char	*cmd_path;

	if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	// setup_child_signals();
	handle_redirection_child(cmd);
	if (!cmd->cmd)
		exit(0);
	if (handle_directory_command(cmd->args[0]) == 999)
		exit(999);
	builtin_status = is_built_ins(cmd->args, env);
	if (builtin_status != 999)
		exit(builtin_status);
	cmd_path = find_executable_path(cmd->args[0], *env);
	if (!cmd_path)
	{
		handle_command_not_found(cmd->args[0]);
		exit(127);
	}
	execute_child_process(cmd_path, cmd->args, *env);
}

int	ft_execute_command_list(t_command *cmd_list, char ***env_ptr, int ex_status)
{
	pid_t	pid;
	int		heredoc_fd;

	if (!cmd_list)
		return (0);
	heredoc_fd = -1;
	if (cmd_list->heredoc_delimiter)
	{
		heredoc_fd = setup_heredoc(cmd_list, *env_ptr, ex_status);
		if (heredoc_fd == -1)
			return (1);
	}
	if (cmd_list->next)
		return (execute_pipeline(cmd_list, env_ptr));
	if (cmd_list->cmd && is_parent_only_builtin(cmd_list->cmd)
		&& !has_redirection(cmd_list))
		return (is_built_ins(cmd_list->args, env_ptr));
	pid = fork();
	if (pid == -1)
		return (handle_fork_error(NULL));
	if (pid == 0)
		child_process_logic(cmd_list, env_ptr, heredoc_fd);
	if (heredoc_fd != -1)
		close(heredoc_fd);
	return (wait_for_child(pid));
}
