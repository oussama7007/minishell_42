/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:12:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/01 16:49:53 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*Handle_regular_accumualtor(char *var_start, char *end,char **env, char *accumulator)
{
	char		*var_name;
	char		*var_value;
	const char	*value_to_join;
	char		*tmp;

	var_name = ft_strndup(var_start, end - var_start);
	var_value = get_var_value(var_name, env);
	free(var_name);
	value_to_join = var_value;
	if (!value_to_join)
		value_to_join = "";
	if (accumulator)
	{
		tmp = accumulator;
		accumulator = ft_strjoin(tmp, value_to_join);
		free(tmp);
	}
	else
		accumulator = ft_strdup(value_to_join);
	return (accumulator);
}

static char	*singel_quotes_handler(char **input_start, t_data *data)
{
	char	*start;
	char	*end;
	char	*accumulator;

	start = *input_start + 1;
	end = start;
	while (*end && *end != '\'')
		end++;
	if (*end != '\'')
		return (NULL);
	accumulator = ft_strndup(start, end - start);
	*input_start = end + 1;
	if (!data->delimiter)
		data->delimiter = 0;
	return (accumulator);
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

char	*handle_double_quote_var(char **end, char **env, char *accumulator)
{
	char	*var_start;

	var_start = *end;
	while (**end && **end != '"' && (ft_isalnum(**end) || **end == '?'))
		(*end)++;
	return (Handle_regular_accumualtor(var_start, *end, env, accumulator));
}
char	*handle_double_quotes(char **start, char **env, t_data *data)
{
	char	*end;
	char	*accumulator;

	end = *start + 1;
	accumulator = ft_strdup("");
	while (*end && *end != '"')
	{
		if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '?')
			&& !data->delimiter)
			accumulator = handle_double_quote_var1(&end, env, data, accumulator);
		else
			accumulator = append_char(accumulator, *end++);
		if (!accumulator)
			return (NULL);
	}
	if (*end != '"')
		return (free(accumulator), NULL);
	*start = end + 1;
	return (accumulator);
}

char	*handle_normal_char(char **end_ptr, char *accumulator, t_data *data)
{
	char		ch;
	char		*tmp;
	char		*new_accumulator;

	ch = **end_ptr;
	tmp = ft_strndup(&ch, 1);
	if (accumulator)
		new_accumulator = join_and_free(accumulator, tmp);
	else
		new_accumulator = tmp;
	(*end_ptr)++;
	data->delimiter = 0;
	return (new_accumulator);
}

char	*handle_unquoted_part(char **start, char **env, t_data *data)
{
	char	*end;
	char	*accumulator;

	end = *start;
	accumulator = NULL;
	data->quote_type = 0;
	while (*end && !is_space(*end) && !is_operator(*end) && !is_quotes(*end))
	{
		if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '?'
			|| *(end + 1) == '"') && !data->delimiter)
			accumulator = handle_dollar_case(&end, env, accumulator, data);
		else
			accumulator = handle_normal_char(&end, accumulator, data);
	}
	*start = end;
	if (!accumulator)
		return (ft_strdup(""));
	return (accumulator);
}

t_token	*handle_word(char **start, char **my_env, t_data *data)
{
	char	*accumulator;
	char	*segment;
	char	*tmp;
	t_token	*token;

	accumulator = NULL;
	while (**start && !is_space(**start) && !is_operator(**start))
	{
		segment = process_segment(start, my_env, data);
		if (!segment)
			return (free(accumulator), NULL);
		if (accumulator)
		{
			tmp = accumulator;
			accumulator = join_and_free(tmp, segment);
		}
		else
			accumulator = segment;
	}
	if (!accumulator)
		accumulator = ft_strdup("");
	token = new_token(get_token_type(accumulator), accumulator, data->quote_type);
	free(accumulator);
	return (token);
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
