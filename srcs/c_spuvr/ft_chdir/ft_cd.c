/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:48 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/12 09:02:48 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static char	*get_old_pwd_val(char **envp)
{
	char	*pwd_val;
	char	*pwd_copy;

	pwd_val = my_getenv("PWD", envp);
	if (pwd_val && *pwd_val)
	{
		pwd_copy = ft_strdup(pwd_val);
		return (pwd_copy);
	}
	pwd_copy = getcwd(NULL, 0);
	if (!pwd_copy)
	{
		ft_putstr_fd("minishell: cd : error retrieving current directory: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (pwd_copy);
}

static int	cd_err(const char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd((char *)path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int	ft_chdir(char **args, char ***env_ptr)
{
	char	*dest;
	char	*old_loc;
	int		ret;
	char	*key_arg;

	old_loc = get_old_pwd_val(*env_ptr);
	dest = target_path(args, *env_ptr);
	if (!dest)
	{
		free(old_loc);
		return (1);
	}
	ret = chdir(dest);
	if (ret == -1)
	{
		cd_err(dest);
		free(old_loc);
		free(dest);
		return (1);
	}
	key_arg = args[1];
	if (!args[1] || (args[1] && ft_strcmp(args[1], "-") == 0))
		key_arg = dest;
	up_env_cd(old_loc, key_arg, env_ptr);
	return (free(old_loc), free(dest), 0);
}
