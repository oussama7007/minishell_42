/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:20:01 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/25 15:16:47 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

static int	is_n_option(const char *arg)
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

static int	is_nn_option(const char *arg)
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

int	ft_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	while ((args[i] && is_n_option(args[i])) || (args[i] && is_nn_option(args[i])))
	{
		n = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	ft_pwd(char ***env_ptr)
{
	char	*current_pwd;
	char	*buffer;

	current_pwd = my_getenv("PWD", *env_ptr);
	if (current_pwd && *current_pwd) // Check if PWD exists and is not empty
	{
		ft_putstr_fd(current_pwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		// free(current_pwd);
		return (0);
	}
	else
	{
		if (getcwd(buffer, sizeof(buffer)) == NULL)
		{
			ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			return (1);
		}
		ft_putstr_fd(buffer, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
}

