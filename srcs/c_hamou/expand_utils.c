/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:45:58 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/11 22:59:18 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_words_from_split(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		i++;
	return (i);
}

void	assign_values_to_prevent_ambigu(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->has_whit_space = 1;
}

void	process_word(char *word, t_token **head, int *flag)
{
	t_data	temp_data;

	if (*flag)
	{
		assign_values_to_prevent_ambigu(&temp_data);
		*flag = 0;
	}
	else
		ft_bzero(&temp_data, sizeof(t_data));
	temp_data.accumulator = word;
	add_token(head, new_token(T_WORD, &temp_data));
}
t_token	*create_tokens_from_split(char **split_words)
{
	t_token	*head;
	int		i;
	t_data	temp_data;
	int		count_words;
	int		flag;

	head = NULL;
	i = 0;
	count_words = count_words_from_split(split_words);
	flag = (count_words > 1);
	if (!split_words || !split_words[0])
		return (NULL);
    while (split_words[i])
		process_word(split_words[i++], &head, &flag);
	return (head);
}

void	process_operator_data(char *operator_str, t_data *data)
{
	data->accumulator = operator_str;
	data->quote_type = 0;
	data->is_expanded = 0;
	data->empty_expand = 0;
	data->is_assigning_expand = 0;
	data->has_whit_space = 0;
}
