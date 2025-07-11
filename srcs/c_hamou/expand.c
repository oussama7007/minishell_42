/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:20:52 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/11 05:32:19 by oait-si-         ###   ########.fr       */
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
	{
		(*end)++;
		return ;
	}
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
int 	count_words_from_split(char **words)
{
	int i;
	
	i = 0;
	while(words[i])
		i++;
	return i;
}
void 	assign_values_to_prevent_ambigu(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->has_whit_space = 1;
}
t_token	*create_tokens_from_split(char **split_words)
{
	t_token	*head;
	int		i;
	t_data	temp_data;
	int 	count_words;
	int flag;
	count_words = count_words_from_split(split_words);
	head = NULL;
	i = 0;
	if(count_words > 1)
		flag = 1;
	if (!split_words || !split_words[0])
		return (NULL);
	while (split_words[i])
	{
		if(flag)
		{
			assign_values_to_prevent_ambigu(&temp_data);
			flag = 0;
		}
		else 
			ft_bzero(&temp_data, sizeof(t_data));
		temp_data.accumulator = split_words[i];
		add_token(&head, new_token(T_WORD, &temp_data));
		i++;
	}
	return (head);
}
