/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:34:06 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/02 22:01:32 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static char	*expand_heredoc_line(char *line, char **env, t_data *data)
{
	char	*result;
	char	*current;

	result = NULL;
	current = line;
	while (*current)
	{
		if (*current == '$' && (ft_isalpha(*(current + 1))
				|| *(current + 1) == '?' || *(current + 1) == '_'))
		{
			result = handle_dollar_case(&current, env, result, data);
		}
		else
		{
			result = handle_normal_char(&current, result, data);
		}
	}
	if (result)
		return (result);
	return (ft_strdup(""));
}

static char	*generate_heredoc_filename(void)
{
	static int	heredoc_count;
	char		*num;
	char		*filename;

	num = ft_itoa(heredoc_count++);
	if (!num)
		return (NULL);
	filename = ft_strjoin("/tmp/minishell-heredoc-", num);
	free(num);
	return (filename);
}

static char	*setup_heredoc_to_file(t_command *cmd, char **envp, t_data *data)
{
	int		fd;
	char	*line;
	char	*filename;
	int		i;

	filename = generate_heredoc_filename();
	if (!filename)
		return (NULL);
	i = -1;
	while (++i < cmd->num_heredocs)
	{
		if (i == cmd->num_heredocs - 1)
		{
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
			if (fd == -1)
				return (free(filename), NULL);
		}
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->heredoc_delimiters[i]) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		if (cmd->heredoc_quotes == 0)
			line = expand_heredoc_line(line, envp, data);
		if (i == cmd->num_heredocs - 1)
			ft_putendl_fd(line, fd);
			
		free(line);
	}
	if (cmd->num_heredocs > 0)
		close(fd);
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
