/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:54:48 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/08 18:42:02 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h"
#include "built_functions.h"

int	ft_export(char **arg, char ***env_ptr)
{
	int		i;
	char	**crr_env;

	if(!env_ptr || !(*env_ptr))
		return (1);
	if (!arg)
	{
		i = 0;
		crr_env = *env_ptr;
		while (crr_env[i])
		{
			ft_putstr_fd(crr_env[i], STDOUT_FILENO);
			ft_putchar_fd("\n", STDOUT_FILENO);
			i++;
		}
	}
	else
	{
		i = find_var_index(arg[0], *env_ptr);
		crr_env = *env_ptr[i];
		ft_putstr_fd(crr_env[i], STDOUT_FILENO);
		ft_putchar_fd("\n", STDOUT_FILENO);
	}
	return (0);
}
