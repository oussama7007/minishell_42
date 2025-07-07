/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:46:06 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/07 10:20:04 by oait-si-         ###   ########.fr       */
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
	token = new_token(get_token_type(operator_str), operator_str, 0, 0);
	free(operator_str);
	return (token);
}
