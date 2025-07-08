/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:24:16 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/08 18:30:11 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	handle_command_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}

int	handle_fork_error(char *cmd_to_free)
{
	if (cmd_to_free)
		free(cmd_to_free);
	ft_putstr_fd("minishell: fork: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}
