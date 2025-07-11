/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:02:29 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/11 14:54:52 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

int	should_stop_reading(char *line, t_heredoc_info *info)
{
	return (!line || ft_strcmp(line, info->cmd->heredoc_delimiters[info->i]) == 0);
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
