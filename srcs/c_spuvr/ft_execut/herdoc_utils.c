/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:34:22 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/07 10:47:58 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

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

char	*generate_heredoc_filename(void)
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
