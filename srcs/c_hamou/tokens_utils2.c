/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:16:02 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/12 09:39:54 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_unquoted_part(char **start, char **env, t_data *data)
{
	char	*end;

	end = *start;
	while (*end && !is_space(*end) && !is_operator(*end) && !is_quotes(*end))
	{
		if (*end == '=' && *(end + 1) == '$')
			data->is_assigning_expand = 1;
		if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '?')
			&& !data->delimiter)
		{
			data->has_unquoted_expansion = 1;
			handle_dollar_case(&end, env, data);
		}
		else
		{
			handle_normal_char(&end, data);
			data->delimiter = 0;
		}
	}
	*start = end;
}

void	process_segment(char **start, char **env, t_data *data)
{
	if (**start == '\'' || **start == '"')
		handle_quoted_part(start, env, data);
	else
		handle_unquoted_part(start, env, data);
}

t_token	*new_token(int type, t_data *data)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(data->accumulator);
	token->quotes_type = data->quote_type;
	token->is_expanded_token = data->is_expanded;
	token->has_unquoted_expansion_token = data->has_unquoted_expansion;
	token->is_empty_after_expand = data->empty_expand;
	token->is_assigning_expand_token = data->is_assigning_expand;
	token->has_whit_space = data->has_whit_space;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *token)
{
	t_token	*tmp;

	if (!*tokens)
	{
		*tokens = token;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
}

int	get_token_type(char *line, t_data *data)
{
	if (ft_strcmp(line, "|") == 0 && data->quote_type == 0)
		return (T_PIPE);
	if (ft_strcmp(line, "<") == 0 && data->quote_type == 0)
		return (T_RED_IN);
	if (ft_strcmp(line, ">") == 0 && data->quote_type == 0)
		return (T_RED_OUT);
	if (ft_strcmp(line, "<<") == 0 && data->quote_type == 0)
		return (T_HEREDOC);
	if (ft_strcmp(line, ">>") == 0 && data->quote_type == 0)
		return (T_APPEND);
	return (T_WORD);
}
