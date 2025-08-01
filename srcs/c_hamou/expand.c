/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:20:52 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/13 02:47:31 by oadouz           ###   ########.fr       */
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

void	handle_dollar_case(char **end, char **env, t_data *data)
{
	(*end)++;
	if (**end == '?')
		handle_question_mark(end, data);
	else if (ft_isalpha(**end))
		handle_regular_dollar(end, env, data);
	else if (ft_isdigit(**end))
		(*end)++;
	else
		data->accumulator = append_char(data->accumulator, '$');
}

void	handle_regular_dollar(char **end, char **env, t_data *data)
{
	char	*var_start;

	var_start = *end;
	while (**end && ft_isalnum(**end))
		(*end)++;
	handle_regular_accumulator(var_start, *end, env, data);
}

void	handle_regular_accumulator(char *var_start, char *end,
		char **env, t_data *data)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;

	var_name = ft_strndup(var_start, end - var_start);
	var_value = get_var_value(var_name, env);
	free(var_name);
	data->is_expanded = 1;
	if (var_value)
	{
		data->has_unquoted_expansion = 1;
		data->is_expanded = 1;
		if (data->accumulator)
		{
			tmp = data->accumulator;
			data->accumulator = ft_strjoin(tmp, var_value);
			free(tmp);
		}
		else
			data->accumulator = ft_strdup(var_value);
	}
}

int	check_heredoc_limit(t_cmd_builder *builder, t_data *data,
		int *total_heredocs)
{
	builder->heredoc_count++;
	(*total_heredocs)++;
	if (*total_heredocs > 16)
	{
		write(2, "minishell: maximum here-document count exceeded\n", 48);
		data->ex_status = 2;
		return (0);
	}
	return (1);
}
