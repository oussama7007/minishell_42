/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:22:45 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/18 17:26:31 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

// static int	is_numeric_arg(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[0] == '+' || str[0] == '-')
// 		i++;
// 	while (str[i])
// 	{
// 		if (!ft_isdigit(str[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// static void	handle_exit_cleanup(t_shell_data *data)
// {
// 	ft_putendl_fd("exit", 2);
	
// 	// Free all resources before exiting
// 	if (data)
// 	{
// 		// Free your environment
// 		if (data->env)
// 			free_environment(data->env);
		
// 		// Free any command history
// 		rl_clear_history();
		
// 		// Free any other allocated resources
// 		// This depends on your shell's specific structure
// 		free_shell_data(data);
// 	}
// }

// static void	exit_with_numeric_error(char *arg, t_shell_data *data)
// {
// 	ft_putstr_fd("minishell: exit: ", 2);
// 	ft_putstr_fd(arg, 2);
// 	ft_putendl_fd(": numeric argument required", 2);
	
// 	handle_exit_cleanup(data);
// 	exit(255);
// }

// int	ft_exit(char **args, t_shell_data *data)
// {
// 	long long	exit_code;
	
// 	if (!args[1])
// 	{
// 		// No arguments - exit with last status
// 		handle_exit_cleanup(data);
// 		exit(data->last_status);
// 	}
	
// 	if (!is_numeric_arg(args[1]))
// 		exit_with_numeric_error(args[1], data);
	
// 	if (args[2])
// 	{
// 		// Too many arguments
// 		ft_putendl_fd("exit", 2);
// 		ft_putendl_fd("minishell: exit: too many arguments", 2);
// 		return (1);
// 	}
	
// 	exit_code = ft_atoi_long(args[1]) % 256;
// 	handle_exit_cleanup(data);
// 	exit((int)exit_code);
// }



