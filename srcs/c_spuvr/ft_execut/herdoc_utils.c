/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:34:22 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/05 22:43:03 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

char	*expand_heredoc_line(char *line, char **env, t_data *data)
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
