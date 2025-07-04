/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:43:39 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/03 21:29:46 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"
#include <signal.h>

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
//	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigquit(int sig)
{
	(void)sig;
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

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
