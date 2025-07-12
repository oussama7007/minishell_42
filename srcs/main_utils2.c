/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:49:42 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/12 18:39:18 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_spuvr/built_functions.h"

int	check_redirection_syntax(t_token *current, t_token *next, t_data *data)
{
	if (!next)
		return (error(ERR_NEWLINE), data->ex_status = 2, 0);
	if (next->type != TOKEN_WORD)
		return (error(ERR_SYNTAX), data->ex_status = 2, 0);
	if ((current->type != TOKEN_RED_HEREDOC
			&& next->is_empty_after_expand
			&& next->quotes_type == 0)
		|| next->has_whit_space)
		return (error(ERR_AMBIGUOS), data->ex_status = 1, 0);
	return (1);
}

void	replace_token(t_token **current_ptr, t_token *token_to_process,
		char **split_words)
{
	t_token	*new_tokens;
	t_token	*end_of_new;

	new_tokens = create_tokens_from_split(split_words);
	if (!new_tokens)
		return ;
	end_of_new = new_tokens;
	while (end_of_new->next)
		end_of_new = end_of_new->next;
	end_of_new->next = token_to_process->next;
	*current_ptr = new_tokens;
	token_to_process->next = NULL;
	free_tokens(&token_to_process);
}

void	process_token_split(t_token **current_ptr)
{
	t_token	*token_to_process;
	char	**split_words;
	t_token	*new_tokens;
	t_token	*next_token;

	token_to_process = *current_ptr;
	if (!should_split_token(token_to_process))
		return ;
	split_words = ft_split(token_to_process->value, ' ');
	if (!split_words)
		return ;
	new_tokens = create_tokens_from_split(split_words);
	next_token = token_to_process->next;
	if (new_tokens)
	{
		*current_ptr = new_tokens;
		while (new_tokens->next)
			new_tokens = new_tokens->next;
		new_tokens->next = next_token;
	}
	else
		*current_ptr = next_token;
	token_to_process->next = NULL;
	free_tokens(&token_to_process);
	free_double(split_words);
}

int	validate_tokens(t_token **tokens, t_data *data, char **line)
{
	(void)line;
	if (!*tokens)
		return (0);
	if ((*tokens)->type == T_PIPE)
	{
		error(ERR_PIPE);
		data->ex_status = 2;
		return (0);
	}
	return (1);
}

int	prepare_execution(t_command **cmds, t_token **tokens,
		char ***env, t_data *data)
{
	if (*cmds)
		free_command(*cmds);
	*cmds = build_command(*tokens);
	if (!*cmds)
	{
		free_tokens(tokens);
		return (0);
	}
	if (!handle_heredocs_before_execution(*cmds, *env, data))
	{
		free_command(*cmds);
		*cmds = NULL;
		free_tokens(tokens);
		return (0);
	}
	return (1);
}
