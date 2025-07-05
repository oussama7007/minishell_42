/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:20:52 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/05 16:30:35 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_var_value(char *new_word, char **envp)
{
	int	var_len;

	if (!new_word || !envp)
		return (NULL);
	var_len = ft_strlen(new_word);
	while (*envp)
	{
		if (ft_strncmp(*envp, new_word, var_len) == 0
			&& (*envp)[var_len] == '=')
			return (*envp + var_len + 1);
		envp++;
	}
	return (NULL);
}

char	*handle_regular_dollar(char **end, char **env,t_data *data)
{
	char	*var_start;

	var_start = *end;
	while (**end && (ft_isalnum(**end) || **end == '?') && !is_space(**end)
		&& !is_operator(**end) && !is_quotes(**end))
		(*end)++;
	return (handle_regular_accumulator(var_start, *end, env, data));
}

char	*handle_dollar_case(char **end, char **env, t_data *data)
{
	(*end)++;
	if (**end == '?')
		return (handle_question_mark(end, data));
	else if (**end == '"')
		return (handle_double_quote_dollar(end, env, data));
	return (handle_regular_dollar(end, env, data ));
}

char	*handle_double_quote_dollar(char **end, 
			char **env, t_data *data)
{
	char	*quoted_value;
	char	*tmp;

	quoted_value = handle_quoted_part(end, env, data);
	if (!quoted_value)
		return (NULL);
	if (data->accumulator)
	{
		tmp = data->accumulator;
		data->accumulator = join_and_free(tmp, quoted_value);
	}
	else
		data->accumulator = quoted_value;
	return (data->accumulator);
}

char	*handle_double_quote_var1(char **end, char **env,
			t_data *data)
{
	char	*tmp;
	char	*new_accumulator;

	(*end)++;
	if (**end == '?')
	{
		tmp = question_mark(data->ex_status);
		new_accumulator = join_and_free(data->accumulator, tmp);
		(*end)++;
		data->accumulator = new_accumulator;
		return (data->accumulator);
	}
	else
		return (handle_double_quote_var(end, env, data));
}
