/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:34:22 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/10 13:10:39 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

char	*generate_heredoc_filename(void)
{
	static int	num_heredocs;
	char		*num;
	char		*filename;

	num = ft_itoa(num_heredocs++);
	if (!num)
		return (NULL);
	filename = ft_strjoin("/tmp/.baya", num);
	free(num);
	return (filename);
}

void	process_heredoc_line(t_heredoc_info *info, char *line)
{
	if (info->fd != -1)
		re_process_heredoc_line(info, line);
	free(line);
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
