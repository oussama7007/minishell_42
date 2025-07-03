/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:22:02 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/03 15:46:58 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

void	try_paths(char **paths, char *cmd, char **cmd_path)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		*cmd_path = join_path(paths[i], cmd);
		if (*cmd_path && access(*cmd_path, X_OK) == 0)
			break ;
		free(*cmd_path);
		*cmd_path = NULL;
		i++;
	}
}

int	is_direct_path(const char *cmd_name)
{
	if (!cmd_name || !*cmd_name)
		return (0);
	return (cmd_name[0] == '/' || cmd_name[0] == '.'
		|| (cmd_name[0] == '.' && cmd_name[1] == '.'
			&& cmd_name[2] == '/'));
}

void	execute_child_process(char *cmd_path, char **args, char **envp)
{
	execve(cmd_path, args, envp);
	ft_putstr_fd(args[0], 2);
	if (errno == ENOEXEC)
	{
		ft_putstr_fd(": Exec format error\n", 2);
		exit(126);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	if (errno == EACCES || errno == EISDIR || errno == ENOTDIR)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(1);
}

void	ft_execute_external(char **args, char **envp)
{
	char	*cmd_path;

	if (!args || !args[0])
		exit(0);
	cmd_path = find_executable_path(args[0], envp);
	if (cmd_path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(cmd_path, args, envp);
	perror("execve");
	free(cmd_path);
	exit(1);
}
