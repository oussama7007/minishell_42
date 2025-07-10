/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:43 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/10 21:38:59 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

char *target_path(char **args, char **envp)
{
	char	*path;
	char	*path_val;
	char	*rest_of_path;

	path = NULL;
	if (!args[1] || args[1][0] == '\0')
	{
		path_val = my_getenv("HOME", envp);
		if (!path_val)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else if (path_val[0] == '\0')
			path = ft_strdup(".");
		else
			path = ft_strdup(path_val);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path_val = my_getenv("OLDPWD", envp);
		if (!path_val || path_val[0] == '\0')
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		else
		{
			ft_putendl_fd(path_val, 1);
			path = ft_strdup(path_val);
		}
	}
	else if (args[1][0] == '~')
	{
		path_val = my_getenv("HOME", envp);
		if (!path_val || path_val[0] == '\0')
			path = ft_strdup(args[1]);
		else
		{
			rest_of_path = ft_substr(args[1], 1, ft_strlen(args[1]) - 1);
			if (rest_of_path)
			{
				path = ft_strjoin(path_val, rest_of_path);
				free(rest_of_path);
			}
		}
	}
	else
		path = ft_strdup(args[1]);
	return (path);
}

static char	*join_pwd(const char *base, const char *arg)
{
	char	*tmp;
	char	*result;
	size_t	base_len;

	if (!arg && base)
		return (ft_strdup(base));
	if (!arg && !base)
		return (NULL);
	if (arg[0] == '/')
		return (ft_strdup(arg));
	if (!base || base[0] == '\0')
		return (ft_strdup(arg));
	base_len = ft_strlen(base);
	if (base_len > 0 && base[base_len - 1] == '/')
	{
		result = ft_strjoin(base, arg);
		return (result);
	}
	tmp = ft_strjoin(base, "/");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, arg);
	free(tmp);
	return (result);
}

void	up_env_cd(char *old_pwd_val, const char *path_arg, char ***env_ptr)
{
	char	*new_pwd;
	char	*new_pwd_val;

	if (old_pwd_val)
		my_setenv("OLDPWD", old_pwd_val, env_ptr);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		my_setenv("PWD", new_pwd, env_ptr);
		free(new_pwd);
	}
	else
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		new_pwd_val = join_pwd(old_pwd_val, path_arg);
		if (new_pwd_val)
		{
			my_setenv("PWD", new_pwd_val, env_ptr);
			free(new_pwd_val);
		}
	}
}
