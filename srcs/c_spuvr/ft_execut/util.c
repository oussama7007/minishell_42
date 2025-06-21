/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:20:30 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/21 16:24:44 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

int	is_parent_only_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "cd") == 0)
        return (1);
    if (ft_strcmp(cmd, "export") == 0)
        return (1);
    if (ft_strcmp(cmd, "unset") == 0)
        return (1);
    if (ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0);
}

int	has_redirection(t_command *cmd)
{
	if ((cmd->red_in && cmd->red_in[0])
		|| (cmd->red_out && cmd->red_out[0])
		|| cmd->heredoc_delimiter)
		return (1);
	return (0);
}
