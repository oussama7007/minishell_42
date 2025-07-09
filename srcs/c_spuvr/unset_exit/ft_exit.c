/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:22:45 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/09 22:36:59 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static int	is_numeric_arg(char *str)
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

static void	cleanup_and_exit(t_data *data, char **env, t_command *cmd, t_token *tok)
{
	if (env)
		free_environment(env);
	if (cmd)
		free_command(cmd);
	if (tok)
		free_tokens(tok);
	//rl_clear_history();
	exit(data->ex_status);
}

int	ft_exit(/*i need to include parameters here but ofc >= 4 less equal or less than 4*/)
{
	// we need to make it in the builtins , and make it as builtins

	ft_putendl_fd("exit", 1);
	if (!args[1])
		cleanup_and_exit(data, *env, cmd, tok);
	if (!is_numeric_arg(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		data->ex_status = 255;
		cleanup_and_exit(data, *env, cmd, tok);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	data->ex_status = ft_atoi(args[1]);
	cleanup_and_exit(data, *env, cmd, tok);
	return (0);
}
