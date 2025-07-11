/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:34:06 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/11 21:54:19 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

int	g_sig_var;

void	heredoc_signals(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	g_sig_var = 1;
}

void	handle_heredoc_interrupt(t_heredoc_info *info, int fd_backup)
{
	if (g_sig_var == 1)
	{
		dup2(fd_backup, STDIN_FILENO);
		info->data->ex_status = 130;
	}
}

void	read_heredoc_input(t_heredoc_info *info)
{
	int	fd_backup;

	g_sig_var = 0;
	fd_backup = dup(STDIN_FILENO);
	signal(SIGINT, &heredoc_signals);
	read_heredoc_loop(info);
	handle_heredoc_interrupt(info, fd_backup);
	setup_signal_handlers();
	close(fd_backup);
}

static int	process_heredoc_iteration(t_heredoc_info *info,
	const char *filename)
{
	if (info->i == info->cmd->num_heredocs - 1)
	{
		info->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (info->fd == -1)
			return (1);
	}
	read_heredoc_input(info);
	if (g_sig_var == 1)
	{
		if (info->fd != -1)
			close(info->fd);
		unlink(filename);
		return (1);
	}
	return (0);
}
