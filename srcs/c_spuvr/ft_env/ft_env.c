/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:33:39 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/12 09:03:48 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

int	ft_env(char **args, char ***env_ptr)
{
	int		i;
	char	*eq_pos;

	(void)args;
	if (!env_ptr || !(*env_ptr))
		return (1);
	i = 0;
	while ((*env_ptr)[i])
	{
		eq_pos = ft_strchr((*env_ptr)[i], '=');
		if (eq_pos)
			ft_putendl_fd((*env_ptr)[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
