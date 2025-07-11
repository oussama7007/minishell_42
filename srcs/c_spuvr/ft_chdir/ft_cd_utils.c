/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:43 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/11 23:09:23 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static char	*get_path_from_home(char **envp)
{
	char	*path_val;

	path_val = my_getenv("HOME", envp);
	if (!path_val)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	if (path_val[0] == '\0')
		return (ft_strdup("."));
	return (ft_strdup(path_val));
}

static char	*get_path_from_oldpwd(char **envp)
{
	char	*path_val;

	path_val = my_getenv("OLDPWD", envp);
	if (!path_val || path_val[0] == '\0')
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	ft_putendl_fd(path_val, 1);
	return (ft_strdup(path_val));
}

static char	*get_path_from_tilde(const char *arg, char **envp)
{
	char	*path_val;
	char	*rest_of_path;
	char	*path;

	path_val = my_getenv("HOME", envp);
	if (!path_val || path_val[0] == '\0')
		return (ft_strdup(arg));
	rest_of_path = ft_substr(arg, 1, ft_strlen(arg) - 1);
	if (!rest_of_path)
		return (NULL);
	path = ft_strjoin(path_val, rest_of_path);
	free(rest_of_path);
	return (path);
}

char	*target_path(char **args, char **envp)
{
	if (!args[1] || args[1][0] == '\0')
		return (get_path_from_home(envp));
	if (ft_strcmp(args[1], "-") == 0)
		return (get_path_from_oldpwd(envp));
	if (args[1][0] == '~')
		return (get_path_from_tilde(args[1], envp));
	return (ft_strdup(args[1]));
}
