/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:19:08 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/23 16:26:24 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

void	handle_redirection_child(t_command *cmd_node)
{
	int	fd_in;
	int	fd_out;

	fd_in = -1;
	fd_out = -1;
	// input redirection dyal > or >>
	if (cmd_node->red_out && cmd_node->red_out[0])
	{
		if (cmd_node->append && cmd_node->append[0])
			fd_out = open(cmd_node->red_out[0], O_WRONLY | O_CREAT |O_APPEND, 0644);
		else
			fd_out = open(cmd_node->red_out[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			perror("minishell: open output file");
			exit(1);
		}
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 stdout");
			exit(1);
		}
	}
	close (fd_out);
}
