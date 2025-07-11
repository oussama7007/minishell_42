/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:02:29 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/11 22:12:57 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

int	should_stop_reading(char *line, t_heredoc_info *info)
{
	return (!line
		|| ft_strcmp(line, info->cmd->heredoc_delimiters[info->i]) == 0);
}

void	expand_heredoc_line(char *line, char **env, t_data *data)
{
	char	*current;

	free(data->accumulator);
	data->accumulator = NULL;
	current = line;
	while (*current)
	{
		if (*current == '$' && (ft_isalpha(*(current + 1))
				|| *(current + 1) == '?' || *(current + 1) == '_'))
			handle_dollar_case(&current, env, data);
		else
			handle_normal_char(&current, data);
	}
	if (!data->accumulator)
		data->accumulator = ft_strdup("");
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
		if (process_heredoc_iteration(&info, filename))
			return (free(filename), NULL);
		info.i++;
	}
	if (info.fd != -1)
		close(info.fd);
	return (filename);
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

int	handle_heredocs_before_execution(t_command *cmds, char **envp,
	t_data *data)
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
