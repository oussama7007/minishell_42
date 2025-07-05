/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:12:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/05 16:17:48 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*singel_quotes_handler(char **input_start, t_data *data)
{
	char	*start;
	char	*end;
	
	start = *input_start + 1;
	end = start;
	while (*end && *end != '\'')
		end++;
	if (*end != '\'')
		return (NULL);
	data->accumulator = ft_strndup(start, end - start);
	*input_start = end + 1;
	if (!data->delimiter)
		data->delimiter = 0;
	return (data->accumulator);
}

char	*handle_quoted_part(char **start, char **env, t_data *data)
{
	char	quote_type;

	quote_type = **start;
	if (quote_type == '\'')
		return (singel_quotes_handler(start, data));
	else
		return (handle_double_quotes(start, env, data));
}

char	*handle_double_quote_var(char **end, char **env,  t_data *data)
{
	char	*var_start;

	var_start = *end;
	while (**end && **end != '"' && (ft_isalnum(**end) || **end == '?'))
		(*end)++;
	return (handle_regular_accumulator(var_start, *end, env, data));
}

char	*handle_double_quotes(char **start, char **env, t_data *data)
{
	char	*end;
	

	end = *start + 1;
	data->accumulator = ft_strdup("");
	while (*end && *end != '"')
	{
		if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '?')
			&& !data->delimiter)
		{
			data->accumulator = handle_double_quote_var1(&end,
					env, data );
		}
		else
			data->accumulator = append_char(data->accumulator, *end++);
		if (!data->accumulator)
			return (NULL);
	}
	if (*end != '"')
		return (free(data->accumulator), NULL);
	*start = end + 1;
	return (data->accumulator);
}

t_token	*tokenize(char *line, char **my_env, t_data *data)
{
	t_token	*tokens;
	char	*start;
	t_token	*token;

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
		if (!token)
		{
			free_tokens(tokens);
			return (NULL);
		}
		add_token(&tokens, token);
	}
	return (tokens);
}
