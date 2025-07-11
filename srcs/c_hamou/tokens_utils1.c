/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:46:06 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/11 22:54:44 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_normal_char(char **end_ptr, t_data *data)
{
	if (data->accumulator)
		data->accumulator = append_char(data->accumulator, **end_ptr);
	else
		data->accumulator = ft_strndup(*end_ptr, 1);
	(*end_ptr)++;
}

int	get_operator_length(char **start, t_data *data)
{
	int	len;

	len = 1;
	if ((**start == '<' && *(*start + 1) == '<'))
	{
		len = 2;
		data->delimiter = 1;
	}
	else if (**start == '>' && *(*start + 1) == '>')
		len = 2;
	return (len);
}

t_token	*handle_operator(char **start, t_data *data)
{
	char	*operator_str;
	int		len;
	t_token	*token;

	len = get_operator_length(start, data);
	operator_str = ft_strndup(*start, len);
	if (!operator_str)
		return (NULL);
	*start += len;
	process_operator_data(operator_str, data);
	token = new_token(get_token_type(data->accumulator, data), data);
	free(operator_str);
	data->accumulator = NULL;
	return (token);
}

void	remove_current_token(t_token **head, t_token **prev, t_token **current)
{
	t_token	*to_free;

	if (*prev)
		(*prev)->next = (*current)->next;
	else
		*head = (*current)->next;
	to_free = *current;
	*current = (*current)->next;
	to_free->next = NULL;
	free_tokens(to_free);
}

void	remove_empty_tokens(t_token **head)
{
	t_token	*current;
	t_token	*prev;

	if (!head || !*head)
		return ;
	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->is_empty_after_expand && current->quotes_type == 0)
			remove_current_token(head, &prev, &current);
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
