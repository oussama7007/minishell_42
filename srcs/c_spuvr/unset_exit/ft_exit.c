/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:22:45 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/12 23:44:21 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

int	is_numeric_arg(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	cleanup_and_exit(t_exit_data *exit_data)
{
	rl_clear_history();
	if (exit_data->env_ptr && *exit_data->env_ptr)
		free_environment(*(exit_data->env_ptr));
	if (exit_data->commands)
		free_command(exit_data->commands);
	if (exit_data->tokens)
		free_tokens(&exit_data->tokens);
	exit(exit_data->data->ex_status);
}

static void	handle_exit_error(char *arg, t_exit_data *exit_data)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit_data->data->ex_status = 2;
	cleanup_and_exit(exit_data);
}

static int	handle_exit_args(char **args, t_exit_data *exit_data)
{
	if (!is_numeric_arg(args[1]) || !is_valid_long_long(args[1]))
		handle_exit_error(args[1], exit_data);
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		exit_data->data->ex_status = 1;
		return (1);
	}
	exit_data->data->ex_status = (unsigned char)ft_atoll(args[1]);
	cleanup_and_exit(exit_data);
	return (0);
}

int	ft_exit(char **args, t_exit_data *exit_data)
{
	ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		exit_data->data->ex_status = 0;
		cleanup_and_exit(exit_data);
	}
	return (handle_exit_args(args, exit_data));
}
