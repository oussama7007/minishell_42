/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:22:02 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/22 17:24:05 by oadouz           ###   ########.fr       */
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

static void	try_paths(char **paths, char *cmd, char **cmd_path)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		*cmd_path = join_path(paths[i], cmd);
		if (*cmd_path && access(*cmd_path, X_OK) == 0)
			break;
		free(*cmd_path);
		*cmd_path = NULL;
		i++;
	}
}

static int	is_direct_path(char *cmd)
{
	return (cmd[0] == '/' || cmd[0] == '.');
}

char	*find_executable_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*cmd_path;

	if (!cmd || !*cmd || !envp)
		return (NULL);
	if (is_direct_path(cmd))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = my_getenv("PATH", envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	cmd_path = NULL;
	try_paths(paths, cmd, &cmd_path);
	ft_free_array(paths);
	return (cmd_path);
}

int	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
