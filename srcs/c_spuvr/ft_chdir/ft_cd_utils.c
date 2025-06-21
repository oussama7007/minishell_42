/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:43 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/21 17:30:28 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

char	*target_path(char **args, char **envp)
{
	char	*path;

	if (!args[1] || args[1][0] == '\0')
	{
		path = ft_strdup(my_getenv("HOME", envp));
		if (!path || path[0] == '\0')
			return (ft_putstr_fd("HOME not set\n", 2), NULL);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = my_getenv("OLDPWD", envp);
		if (!path || path[0] == '\0')
		{
			ft_putstr_fd("OLDPWD not set\n", 2);
			return (NULL);
		}
		ft_putendl_fd(path, 1);
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
