/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:22:02 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/24 16:32:01 by oadouz           ###   ########.fr       */
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

int	is_direct_path(const char *cmd_name)
{
	if (!cmd_name || !*cmd_name)
		return (0);
	return (cmd_name[0] == '/' || cmd_name[0] == '.'
		|| (cmd_name[0] == '.' && cmd_name[1] == '.' && cmd_name[2] == '/'));
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

void	execute_child_process(char *cmd_path, char **args, char **envp)
{
	execve(cmd_path, args, envp);
	ft_putstr_fd("minishell: pppp ", 2);
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
