/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fuc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:34:08 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/05 22:39:17 by oait-si-         ###   ########.fr       */
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

char	*ft_split_function(char *str)
{
	char	*new;
	int		i;
	int		j;

	if (!str)
		return (ft_strdup(""));
	str = skip_space(str);
	new = malloc(count_char(str) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_space(str[i]))
		{
			new[j++] = ' ';
			while (str[i] && is_space(str[i]))
				i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}
