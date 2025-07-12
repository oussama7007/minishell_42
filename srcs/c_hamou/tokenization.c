/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:12:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/12 21:21:32 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	singel_quotes_handler(char **input_start, t_data *data)
{
	char	*start;
	char	*end;
	char	*segment;

	data->quote_type = 1;
	start = *input_start + 1;
	end = start;
	while (*end && *end != '\'')
		end++;
	segment = ft_strndup(start, end - start);
	if (segment)
		data->accumulator = join_and_free(data->accumulator, segment);
	if (*end == '\'')
		*input_start = end + 1;
	else
		*input_start = end;
}

void	handle_double_quotes(char **start, char **env, t_data *data)
{
	char	*end;

	end = *start + 1;
	while (*end && *end != '"')
	{
		if (*end == '$' && !data->delimiter)
			handle_dollar_case(&end, env, data);
		else
		{
			data->accumulator = append_char(data->accumulator, *end);
			end++;
		}
	}
	if (*end == '"')
		*start = end + 1;
	else
		*start = end;
}

t_token	*handle_word(char **start, char **my_env, t_data *data)
{
	t_token	*token;

	reset_word_data(data);
	while (**start && !is_space(**start) && !is_operator(**start))
		process_segment(start, my_env, data);
	if (data->accumulator && ft_strchr(data->accumulator, ' '))
		data->has_whit_space = 1;
	if (!data->accumulator)
	{
		if (data->is_expanded)
			data->empty_expand = 1;
		data->accumulator = ft_strdup("");
	}
	token = new_token(get_token_type(data->accumulator, data), data);
	free(data->accumulator);
	data->accumulator = NULL;
	return (token);
}

void	handle_quoted_part(char **start, char **env, t_data *data)
{
	if (**start == '\'')
		singel_quotes_handler(start, data);
	else if (**start == '"')
		handle_double_quotes(start, env, data);
}

t_token	*tokenize(char *line, char **my_env, t_data *data)
{
	t_token	*tokens;
	t_token	*token;
	char	*start;

	tokens = NULL;
	start = line;
	while (*start)
	{
		while (is_space(*start))
			start++;
		if (!*start)
			break ;
		if (is_operator(*start))
			token = handle_operator(&start, data);
		else
			token = handle_word(&start, my_env, data);
		if (!create_and_add_token(&tokens, token, data))
			return (NULL);
	}
	return (tokens);
}
