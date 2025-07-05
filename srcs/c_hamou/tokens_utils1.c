/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:46:06 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/05 16:24:22 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*handle_regular_accumulator(char *var_start,
					char *end, char **env, t_data *data)
{
	char		*var_name;
	char		*var_value;
	char		*value_to_join;
	char		*tmp;

	var_name = ft_strndup(var_start, end - var_start);
	var_value = get_var_value(var_name, env);
	free(var_name);
	value_to_join = var_value;
	if (data->accumulator)
	{
		tmp = data->accumulator;
		data->accumulator = ft_strjoin(tmp, value_to_join);
		free(tmp);
	}
	else
		data->accumulator = ft_strdup(value_to_join);
	return (free(value_to_join), data->accumulator);
}

char	*handle_normal_char(char **end_ptr, t_data *data)
{
	char	ch;
	char	*tmp;
	char	*new_accumulator;

	ch = **end_ptr;
	tmp = ft_strndup(&ch, 1);
	if (data->accumulator)
		new_accumulator = join_and_free(data->accumulator, tmp);
	else
		new_accumulator = tmp;
	(*end_ptr)++;
	data->delimiter = 0;
	data->accumulator = new_accumulator;
	return (data->accumulator);
}

char	*handle_unquoted_part(char **start, char **env, t_data *data)
{
	char	*end;
	// char	*accumulator;

	end = *start;
	data->accumulator = NULL;
	data->quote_type_data = 0;
	while (*end && !is_space(*end) && !is_operator(*end)
		&& !is_quotes(*end))
	{
		if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '?'
				|| *(end + 1) == '"') && !data->delimiter)
			data->accumulator = handle_dollar_case(&end, env, data);
		else
			data->accumulator = handle_normal_char(&end,data);
	}
	*start = end;
	if (!data->accumulator)
		return (ft_strdup(""));
	return (data->accumulator);
}

t_token	*handle_word(char **start, char **my_env, t_data *data)
{
	//char	*accumulator;
	char	*segment;
	char	*tmp;
	t_token	*token;

	data->accumulator = NULL;
	while (**start && !is_space(**start) && !is_operator(**start))
	{
		segment = process_segment(start, my_env, data);
		if (!segment)
			return (free(data->accumulator), NULL);
		if (data->accumulator)
		{
			tmp = data->accumulator;
			data->accumulator = join_and_free(tmp, segment);
		}
		else
			data->accumulator = segment;
	}
	if (!data->accumulator)
		data->accumulator = ft_strdup("");
	token = new_token(get_token_type(data->accumulator), data);
	free(data->accumulator);
	return (token);
}
