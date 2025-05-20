/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:54:48 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/20 14:29:58 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

int	is_built_ins(char **cmd, char ***env_ptr)
{
	if ((ft_strcmp(cmd[0], "export")) == 0)
		ft_export(cmd, env_ptr);
	else if ((ft_strcmp(cmd[0], "pwd")) == 0)
		ft_pwd();
	else if ((ft_strcmp(cmd[0], "cd")) == 0)
		ft_chdir(cmd, env_ptr);
	else if ((ft_strcmp(cmd[0], "unset")) == 0)
		ft_unset(cmd, env_ptr);
	else if ((ft_strcmp(cmd[0], "env")) == 0)
		ft_env(cmd, env_ptr);
	else if ((ft_strcmp(cmd[0], "echo")) == 0)
		ft_echo(cmd);
	return (0);
}
