/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:16:56 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/10 00:19:57 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

void	setup_child_io(int prev_pipe, int *pipe_fds, t_command *cmd)
{
	if (prev_pipe != STDIN_FILENO)
	{
		if (dup2(prev_pipe, STDIN_FILENO) == -1)
			exit(1);
		close(prev_pipe);
	}
	if (cmd->next)
	{
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipe_fds[1]);
		close(pipe_fds[0]);
	}
}
