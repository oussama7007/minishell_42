/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:34:06 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/03 15:32:23 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

typedef struct s_heredoc_info
{
	int			fd;
	int			i;
	t_command	*cmd;
	char		**envp;
	t_data		*data;
}	t_heredoc_info;

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
			result = handle_dollar_case(&current, env, result, data);
		else
			result = handle_normal_char(&current, result, data);
	}
	if (result)
		return (result);
	return (ft_strdup(""));
}

static char	*generate_heredoc_filename(void)
{
	static int	num_heredocs;
	char		*num;
	char		*filename;

	num = ft_itoa(num_heredocs++);
	if (!num)
		return (NULL);
	filename = ft_strjoin("/tmp/minishell-heredoc-", num);
	free(num);
	return (filename);
}

static void	read_heredoc_input(t_heredoc_info *info)
{
	char	*line;

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
				line = expand_heredoc_line(line, info->envp, info->data);
			ft_putendl_fd(line, info->fd);
		}
		free(line);
	}
}

static char	*setup_heredoc_to_file(t_command *cmd, char **envp, t_data *data)
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

int	handle_heredocs_before_execution(t_command *cmds, char **envp,
		t_data *data)
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
