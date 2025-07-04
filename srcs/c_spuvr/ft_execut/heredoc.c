/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:34:06 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/04 21:27:29 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"
int g_sig_var;

void	heredoc_signals(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	g_sig_var = 1;
}

static void	read_heredoc_input(t_heredoc_info *info)
{
	int		fd;
	char	*line;
	char	*expanded_line;

	int g_sig_var = 0;
	fd = dup(STDIN_FILENO);
	signal(SIGINT, &heredoc_signals);
	while (1)
	{
		line = readline("> ");
		if (!line
			|| ft_strcmp(line, info->cmd->heredoc_delimiters[info->i]) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		if (info->fd != -1)
		{
			if (info->cmd->heredoc_quotes[info->i] == 0)
				expanded_line = expand_heredoc_line(line, info->envp,
						info->data);
			else
				expanded_line = line;
			ft_putendl_fd(expanded_line, info->fd);
			if (expanded_line != line)
				free(expanded_line);
		}
		free(line);
	}
	if (g_sig_var == 1)
	{
		dup2(fd, 0);
		info->data->ex_status = 130;
		setup_signal_handlers();
	}
}

static char	*setup_heredoc_to_file(t_command *cmd,
		char **envp, t_data *data)
{
	t_heredoc_info	info;
	char			*filename;

	filename = generate_heredoc_filename();
	if (!filename)
		return (NULL);
	info.fd = -1;
	info.i = 0;
	info.cmd = cmd;
	info.envp = envp;
	info.data = data;
	while (info.i < info.cmd->num_heredocs)
	{
		if (info.i == info.cmd->num_heredocs - 1)
		{
			info.fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
			if (info.fd == -1)
				return (free(filename), NULL);
		}
		read_heredoc_input(&info);
		info.i++;
	}
	if (info.fd != -1)
		close(info.fd);
	return (filename);
}

int	handle_heredocs_before_execution(t_command *cmds,
		char **envp, t_data *data)
{
	t_command	*current;

	current = cmds;
	while (current)
	{
		if (current->num_heredocs > 0)
		{
			if (current->heredoc_tmp_file)
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
