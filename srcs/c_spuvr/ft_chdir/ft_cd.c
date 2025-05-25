/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:48 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/25 15:17:55 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static char	*get_old_pwd_val(char **envp)
{
	char	*pwd;

	pwd = my_getenv("PWD", envp);
	if (pwd && pwd[0])
		return (pwd);
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("minishell: cd ikhann: error retrieving current directory: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (pwd);
}

static int	cd_err(const char *path, char *old_loc,
					int free_flag, char *target_to_free)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd((char *)path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	// free(old_loc);
	if (free_flag)
		free(target_to_free);
	return (1);
}

int	ft_chdir(char **args, char ***env_ptr)
{
	char	*dest;
	char	*old_loc;
	int		ret;
	int		free_dest;
	char	*key_arg;

	old_loc = get_old_pwd_val(*env_ptr);
	dest = target_path(args, *env_ptr, &free_dest);
	if (!dest)
	{
		free(old_loc);
		return (1);
	}
	ret = chdir(dest);
	if (ret == -1)
		return (cd_err(dest, old_loc, free_dest, dest));
	key_arg = args[1];
	if (!args[1] || (args[1] && ft_strcmp(args[1], "-") == 0))
		key_arg = dest;
	up_env_cd(old_loc, key_arg, env_ptr);
	if (free_dest == 1)
		free(old_loc);// to rm
	if (free_dest)
		free(dest);
	return (0);
}
