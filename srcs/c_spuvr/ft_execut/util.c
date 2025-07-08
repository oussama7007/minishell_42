/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:20:30 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/08 18:26:00 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

int	is_parent_only_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	has_redirection(t_command *cmd)
{
	if ((cmd->red_in && cmd->red_in[0])
		|| (cmd->red_out && cmd->red_out[0])
		|| cmd->heredoc_delimiters)
		return (1);
	return (0);
}

char	*find_executable_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*cmd_path;

	if (!cmd || !*cmd)
		return (NULL);
	path_env = my_getenv("PATH", envp);
	if (is_direct_path(cmd) || !path_env || !*path_env)
		return (ft_strdup(cmd));
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
