/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:54:48 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/12 18:06:20 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

int	is_built_ins(char **cmd, char ***env_ptr)
{
	if ((ft_strcmp(cmd[0], "export")) == 0)
		return (ft_export(cmd, env_ptr));
	else if ((ft_strcmp(cmd[0], "exit")) == 0)
		return (ft_exit_child(cmd));
	else if ((ft_strcmp(cmd[0], "pwd")) == 0)
		return (ft_pwd(env_ptr));
	else if ((ft_strcmp(cmd[0], "cd")) == 0)
		return (ft_chdir(cmd, env_ptr));
	else if ((ft_strcmp(cmd[0], "unset")) == 0)
		return (ft_unset(cmd, env_ptr));
	else if ((ft_strcmp(cmd[0], "env")) == 0)
		return (ft_env(cmd, env_ptr));
	else if ((ft_strcmp(cmd[0], "echo")) == 0)
		return (ft_echo(cmd));
	return (999);
}
void 	set_to_null(t_command	**commands,t_token **tokens, char **line )
{
	*commands = NULL;
	*tokens = NULL;
	*line = NULL;
}