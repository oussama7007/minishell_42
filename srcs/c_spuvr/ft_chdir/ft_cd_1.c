/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:45 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/11 22:17:59 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

void	up_env_cd(char *old_pwd_val, const char *path_arg, char ***env_ptr)
{
	char	*new_pwd;
	char	*new_pwd_val;

	if (old_pwd_val && my_getenv("OLDPWD", *env_ptr) != NULL)
		my_setenv("OLDPWD", old_pwd_val, env_ptr);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		if (my_getenv("PWD", *env_ptr) != NULL)
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
			if (my_getenv("PWD", *env_ptr) != NULL)
				my_setenv("PWD", new_pwd_val, env_ptr);
			free(new_pwd_val);
		}
	}
}
