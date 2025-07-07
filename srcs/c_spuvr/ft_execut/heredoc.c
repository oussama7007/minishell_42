/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:34:06 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/07 11:05:44 by oait-si-         ###   ########.fr       */
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

void	re_process_heredoc_line(t_heredoc_info *info, char *line)
{
	if (info->cmd->heredoc_quotes[info->i] == 0)
	{
		expand_heredoc_line(line, info->envp, info->data);
		ft_putendl_fd(info->data->accumulator, info->fd);
	}
	else
	{
		ft_putendl_fd(line, info->fd);
	}
}

void	handle_heredoc_interrupt(t_heredoc_info *info, int fd_backup)
{
	if (g_sig_var == 1)
	{
		dup2(fd_backup, STDIN_FILENO);
		info->data->ex_status = 130;
	}
}

void	process_heredoc_line(t_heredoc_info *info, char *line)
{
	if (info->fd != -1)
		re_process_heredoc_line(info, line);
	free(line);
}

int	should_stop_reading(char *line, t_heredoc_info *info)
{
	return (!line || ft_strcmp(line, info->cmd->heredoc_delimiters[info->i]) == 0);
}

void	read_heredoc_loop(t_heredoc_info *info)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (should_stop_reading(line, info))
		{
			free(line);
			break ;
		}
		process_heredoc_line(info, line);
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

char	*setup_heredoc_to_file(t_command *cmd, char **envp, t_data *data)
{
	t_heredoc_info	info;
	char			*filename;

	filename = generate_heredoc_filename();
	if (!filename)
		return (NULL);
	info = (t_heredoc_info){-1, 0, cmd, envp, data};
	while (info.i < info.cmd->num_heredocs)
	{
		if (info.i == info.cmd->num_heredocs - 1)
		{
			info.fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
			if (info.fd == -1)
				return (free(filename), NULL);
		}
		read_heredoc_input(&info);
		if (g_sig_var == 1)
			return (free(filename), NULL);
		info.i++;
	}
	if (info.fd != -1)
		close(info.fd);
	return (filename);
}

int	handle_heredocs_before_execution(t_command *cmds, char **envp, t_data *data)
{
	t_command	*current;

	current = cmds;
	while (current)
	{
		if (current->num_heredocs > 0)
		{
			free(current->heredoc_tmp_file);
			current->heredoc_tmp_file = setup_heredoc_to_file(current,
					envp, data);
			if (!current->heredoc_tmp_file)
				return (0);
		}
		current = current->next;
	}
	return (1);
}
