/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:19:08 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/09 12:23:02 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static int	handle_input_redirection(t_command *cmd_node)
{
	int	fd_in;
	int	i;

	if (!cmd_node->red_in || !cmd_node->red_in[0])
		return (0);
	i = 0;
	while (cmd_node->red_in[i])
	{
		fd_in = open(cmd_node->red_in[i], O_RDONLY);
		if (fd_in == -1)
		{
			perror("minishell: open input file");
			exit(1);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 stdin");
			close(fd_in);
			exit(1);
		}
		close(fd_in);
		i++;
	}
	return (0);
}

static int	handle_output_redirection(t_command *cmd_node)
{
	int	fd_out;
	int	flags;
	int	i;

	if (!cmd_node->red_out || !cmd_node->red_out[0])
		return (0);
	i = 0;
	while (cmd_node->red_out[i])
	{
		flags = O_WRONLY | O_CREAT;
		if (cmd_node->append && cmd_node->append[i])
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd_out = open(cmd_node->red_out[i], flags, 0644);
		if (fd_out == -1)
		{
			perror("minishell: open output file");
			exit(1);
		}
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 stdout");
			close(fd_out);
			exit(1);
		}
		close(fd_out);
		i++;
	}
	return (0);
}

void	handle_redirection_child(t_command *cmd_node)
{
	handle_input_redirection(cmd_node);
	handle_output_redirection(cmd_node);
}
