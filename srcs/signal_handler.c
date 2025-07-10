/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:43:39 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/10 21:03:43 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"

void	setup_child_signals(t_command *cmd)
{
	if (ft_strnstr(cmd->cmd, "minishell", ft_strlen(cmd->cmd)))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);	
	}
}

void	sigint_handler_exec(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	sigint_handler(int sig)
{
	(void)sig;
	exit_status(1, 130, NULL);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}
