/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fuc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:34:08 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/01 16:57:33 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "header.h"
char	*handle_question_mark(char **end, char *accumulator, t_data *data)
{
	char	*status_str;
	char	*tmp;

	status_str = question_mark(data->ex_status);
	if (accumulator)
	{
		tmp = accumulator;
		accumulator = ft_strjoin(tmp, status_str);
		free(tmp);
		free(status_str);
	}
	else
		accumulator = status_str;
	(*end)++;
	return (accumulator);
}

char	*join_and_free(char *acc, char *to_add)
{
	char	*new;

	new = ft_strjoin(acc, to_add);
	free(acc);
	free(to_add);
	return (new);
}
char	*append_char(char *str, char c)
{
	char	ch[2];
	char	*new;

	ch[0] = c;
	ch[1] = '\0';
	if (!str)
		return (ft_strdup(ch));
	new = ft_strjoin(str, ch);
	free(str);
	return (new);
}