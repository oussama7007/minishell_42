/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util99.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 03:09:09 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/13 03:19:05 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	process_tokens(t_cmd_builder *builder, t_token *token,
	t_data *data, int *heredoc_count)
{
	if (token->type == TOKEN_WORD)
		builder->arg_count++;
	else if (token->type == TOKEN_RED_IN && token->next)
		builder->red_in_count++;
	else if (token->type == TOKEN_RED_HEREDOC && token->next)
	{
		if (!check_heredoc_limit(builder, data, heredoc_count))
			return (0);
	}
	else if ((token->type == TOKEN_RED_OUT
			|| token->type == TOKEN_RED_APPEND) && token->next)
		builder->red_out_count++;
	return (1);
}
