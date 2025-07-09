/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/10 00:06:33 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"
#include <sys/stat.h>

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

static void	child_process_logic(t_command *cmd, char ***env)
{
	int	builtin_status;
	int	dir_status;

	if (!handle_redirection_child(cmd))
		exit(1);
	if (!cmd->cmd)
		exit(0);
	if (ft_strcmp(cmd->cmd, "exit") == 0)
	{
		if (!cmd->args[1])
			exit(0);
		if (!is_numeric_arg(cmd->args[1]))
			exit(255);
		if (cmd->args[2])
			exit(1);
		exit((unsigned char)ft_atoi(cmd->args[1]));
	}
	dir_status = handle_directory_command(cmd->args[0]);
	if (dir_status != 0)
		exit(dir_status);
	builtin_status = is_built_ins(cmd->args, env);
	if (builtin_status != 999)
		exit(builtin_status);
	validate_and_execute(cmd, *env);
}

int ft_execute_command_list(t_command *cmd_list, t_token *tokens, char ***env_ptr, t_data *data)
{
	pid_t	pid;
	int		status;

	if (!cmd_list)
		return (0);
	if (cmd_list->cmd && ft_strcmp(cmd_list->cmd, "exit") == 0 && !cmd_list->next)
	{
		t_exit_data exit_data;

		exit_data.env_ptr = env_ptr;
		exit_data.commands = cmd_list;
		exit_data.tokens = tokens;
		exit_data.data = data;
		return (ft_exit(cmd_list->args, &exit_data));
	}
	if (cmd_list->next)
		return (execute_pipeline(cmd_list, env_ptr, data));
	if (cmd_list->cmd && is_parent_only_builtin(cmd_list->cmd)
		&& !has_redirection(cmd_list))
		return (is_built_ins(cmd_list->args, env_ptr));
	pid = fork();
	if (pid == -1)
		return (handle_fork_error(NULL));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process_logic(cmd_list, env_ptr);
	}
	signal(SIGINT, SIG_IGN);
	status = wait_for_child(pid);
	setup_signal_handlers();
	return (status);
}
