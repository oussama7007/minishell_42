/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/22 15:44:58 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"


int	ft_execute_command_list(t_command *command_list, char ***env_ptr)
{
	t_command	*commands = command_list;
	// char		**my_envp = *env_ptr;
	if ((is_built_ins(commands->args, env_ptr)) == 0)
	{
		return (0);
	}
	else (ft_execute_external())
	return (0);
}
