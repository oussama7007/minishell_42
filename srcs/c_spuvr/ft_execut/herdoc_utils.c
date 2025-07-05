/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:34:22 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/05 16:12:59 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

char	*expand_heredoc_line(char *line, char **env, t_data *data)
{

	char	*current;

	data->accumulator = NULL;
	current = line;
	while (*current)
	{
		if (*current == '$' && (ft_isalpha(*(current + 1))
				|| *(current + 1) == '?' || *(current + 1) == '_'))
			data->accumulator = handle_dollar_case(&current, env,  data);
		else
			data->accumulator = handle_normal_char(&current, data);
	}
	if (data->accumulator)
		return (data->accumulator);
	return (ft_strdup(""));
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
