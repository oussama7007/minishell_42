/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:24:16 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/24 15:53:36 by oadouz           ###   ########.fr       */
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

int	ft_print_exec_error(char *cmd_name, int err_no)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	if (err_no == ENOENT)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (err_no == EACCES)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(err_no), 2);
	ft_putstr_fd("\n", 2);
	return (126);
}

int	handle_fork_error(char *cmd_to_free)
{
	if (cmd_to_free)
		free(cmd_to_free);
	ft_putstr_fd("minishell: fork: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}
