/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:20:01 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/11 02:28:50 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

int	is_n_option(const char *arg)
{
	int	j;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	j = 2;
	while (arg[j])
	{
		if (arg[j] != 2)
			return (0);
		j++;
	}
	return (1);
}

int	is_nn_option(const char *arg)
{
	size_t	i;

	i = 0;
	if (!arg)
		return (0);
	if (arg[i] == '-')
	{
		i++;
		while (arg[i] == 'n')
			i++;
		if (arg[i])
			return (0);
		return (1);
	}
	return (0);
}

int	ft_pwd(char ***env_ptr)
{
	char	*current_pwd;
	char	*buffer;

	current_pwd = my_getenv("PWD", *env_ptr);
	if (current_pwd && *current_pwd)
	{
		ft_putstr_fd(current_pwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	else
	{
		buffer = getcwd(NULL, 0);
		if (buffer == NULL)
		{
			perror("minishell: pwd");
			return (1);
		}
		ft_putstr_fd(buffer, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(buffer);
		return (0);
	}
}
