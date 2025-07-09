/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fuc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:34:08 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/09 17:37:36 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_question_mark(char **end, t_data *data)
{
	char	*status_str;

	status_str = question_mark(data->ex_status);
	data->is_expanded = 1;
	if (data->accumulator)
		data->accumulator = join_and_free(data->accumulator, status_str);
	else
		data->accumulator = status_str;
	(*end)++;
}

char	*join_and_free(char *acc, char *to_add)
{
	char	*new;

	new = ft_strjoin(acc, to_add);
	free(acc);
	free(to_add);
	return (new);
}

char	*append_char(char *str, char c)
{
	char	ch[2];
	char	*new;

	ch[0] = c;
	ch[1] = '\0';
	if (!str)
		return (ft_strdup(ch));
	new = ft_strjoin(str, ch);
	free(str);
	return (new);
}

void	reset_word_data(t_data *data)
{
	free(data->accumulator);
	data->accumulator = NULL;
	data->is_expanded = 0;
	data->empty_expand = 0;
	data->quote_type = 0;
}

t_token	*create_and_add_token(t_token **tokens, t_token *token, t_data *data)
{
	if (!token)
	{
		free(data->accumulator);
		data->accumulator = NULL;
		free_tokens(*tokens);
		return (NULL);
	}
	add_token(tokens, token);
	return (*tokens);
}
