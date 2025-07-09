/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:46:06 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/09 03:20:04 by oait-si-         ###   ########.fr       */
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

t_token	*handle_operator(char **start, t_data *data)
{
	char	*operator_str;
	int		len;
	t_token	*token;

	len = 1;
	if ((**start == '<' && *(*start + 1) == '<')
		|| (**start == '>' && *(*start + 1) == '>'))
	{
		len = 2;
		if (**start == '<' && *(*start + 1) == '<')
			data->delimiter = 1;
	}
	operator_str = ft_strndup(*start, len);
	if (!operator_str)
		return (NULL);
	*start += len;
	data->accumulator = operator_str;
	data->quote_type = 0;
	data->is_expanded = 0;
	data->empty_expand = 0;
	
	token = new_token(get_token_type(data->accumulator), data);
	if (token->type == T_RED_OUT || token->type == T_APPEND)
		data->redirect_context = 1;
	free(operator_str);
	data->accumulator = NULL;
	return (token);
}
