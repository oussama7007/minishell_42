/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:19:45 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/21 02:30:30 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

static void	handle_shlvl_update(char ***env_ptr)
{
	char	*val_shlvl;
	int		shlvl_nb;
	char	*new_shlvl;

	val_shlvl = my_getenv("SHLVL", *env_ptr);
	if (!val_shlvl || !ft_isdigit(*val_shlvl))
		my_setenv("SHLVL", "1", env_ptr);
	else
	{
		shlvl_nb = ft_atoi(val_shlvl) + 1;
		new_shlvl = ft_itoa(shlvl_nb);
		if (new_shlvl)
		{
			my_setenv("SHLVL", new_shlvl, env_ptr);
			free(new_shlvl);
		}
	}
}

void	ensure_minimal_env(char ***env_ptr)
{
	char	*pwd_buffer;

	if (!my_getenv("PATH", *env_ptr))
		my_setenv("PATH", "/usr/bin:/bin:/usr/sbin:/sbin", env_ptr);
	handle_shlvl_update(env_ptr);
	if (!my_getenv("PWD", *env_ptr))
	{
		pwd_buffer = getcwd(NULL, 0);
		if (pwd_buffer)
		{
			my_setenv("PWD", pwd_buffer, env_ptr);
			free(pwd_buffer);
		}
	}
}
