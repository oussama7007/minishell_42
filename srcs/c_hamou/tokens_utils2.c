/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:16:02 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/07 10:16:27 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_unquoted_part(char **start, char **env, t_data *data)
{
	char	*end;

	end = *start;
	data->quote_type = 0;
	while (*end && !is_space(*end) && !is_operator(*end) && !is_quotes(*end))
	{
		if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '?')
			&& !data->delimiter)
			handle_dollar_case(&end, env, data);
		else
		{
			handle_normal_char(&end, data);
			if (data->delimiter)
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

t_token	*new_token(int type, char *value, int quotes_type, int is_expanded)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->quotes_type = quotes_type;
	token->is_expanded_token = is_expanded;
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

int	get_token_type(char *line)
{
	if (ft_strcmp(line, "|") == 0)
		return (T_PIPE);
	if (ft_strcmp(line, "<") == 0)
		return (T_RED_IN);
	if (ft_strcmp(line, ">") == 0)
		return (T_RED_OUT);
	if (ft_strcmp(line, "<<") == 0)
		return (T_HEREDOC);
	if (ft_strcmp(line, ">>") == 0)
		return (T_APPEND);
	return (T_WORD);
}
