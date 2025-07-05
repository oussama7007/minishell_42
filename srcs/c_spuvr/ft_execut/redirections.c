/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:19:08 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/05 02:35:49 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static int	open_and_dup_input(char *filename)
{
	int	fd_in;

	fd_in = open(filename, O_RDONLY);
	if (fd_in == -1)
	{
		perror("minishell: open input file");
		return (0);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 stdin");
		close(fd_in);
		return (0);
	}
	close(fd_in);
	return (1);
}

static int	handle_input_redirection(t_command *cmd_node)
{
	int	i;
	int	status;

	if (!cmd_node->red_in || !cmd_node->red_in[0])
		return (1);
	i = 0;
	status = 1;
	while (cmd_node->red_in[i])
	{
		if (!open_and_dup_input(cmd_node->red_in[i]))
			status = 0;
		i++;
	}
	return (status);
}

static void	open_and_dup_output(char *filename, int flags)
{
	int	fd_out;

	fd_out = open(filename, flags, 0644);
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
}

static int	handle_output_redirection(t_command *cmd_node)
{
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
		open_and_dup_output(cmd_node->red_out[i], flags);
		i++;
	}
	return (0);
}

int	handle_redirection_child(t_command *cmd_node)
{
	int	fd;
	int	status;

	status = 1;
	if (cmd_node->heredoc_tmp_file)
	{
		fd = open(cmd_node->heredoc_tmp_file, O_RDONLY);
		if (fd == -1)
		{
			perror("minishell: heredoc open");
			exit(1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 heredoc");
			close(fd);
			exit(1);
		}
		close(fd);
		unlink(cmd_node->heredoc_tmp_file);
	}
	handle_output_redirection(cmd_node);
	if (!handle_input_redirection(cmd_node))
		status = 0;
	return (status);
}
