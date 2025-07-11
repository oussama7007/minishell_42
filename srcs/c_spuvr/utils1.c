/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:19:45 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/11 22:22:53 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

static void	zft_initialize(int *i, int *s, unsigned long long *r)
{
	*i = 0;
	*s = 1;
	*r = 0;
}

int	shlvl_ft_atoi(const char *str)
{
	int					i;
	unsigned long long	r;
	int					s;

	zft_initialize(&i, &s, &r);
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		if (r > 9223372036854775807 && s == -1)
			return (0);
		if (r > 9223372036854775807 && s == 1)
			return (0);
		i++;
	}
	return (r * s);
}

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
		shlvl_nb = shlvl_ft_atoi(val_shlvl) + 1;
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
		my_setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", env_ptr);
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
	if (!my_getenv("OLDPWD", *env_ptr))
		my_setenv("OLDPWD", NULL, env_ptr);
}
