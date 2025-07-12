/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 03:20:39 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/12 07:42:58 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_spuvr/built_functions.h"

int	is_redirection(int token_type)
{
	return (token_type == TOKEN_RED_IN
		|| token_type == TOKEN_RED_OUT
		|| token_type == TOKEN_RED_APPEND
		|| token_type == TOKEN_RED_HEREDOC);
}

int	should_split_token(t_token *token)
{
	return (token->has_unquoted_expansion_token
		&& !token->is_assigning_expand_token);
}

int	handle_exit(char *line, char ***env, t_data *data)
{
	if (!line)
	{
		write(1, "exit\n", 5);
		free_environment(*env);
		exit(data->ex_status);
	}
	return (0);
}

int	check_pipe_syntax(t_token *current, t_token *next, t_data *data)
{
	if (current->type == TOKEN_PIPE)
	{
		if (!next || next->type == TOKEN_PIPE)
			return (error(ERR_SYNTAX), data->ex_status = 2, 0);
	}
	return (1);
}

int	validate_syntax(t_token *tokens, t_data *data)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (!check_pipe_syntax(current, next, data))
			return (0);
		if (is_redirection(current->type)
			&& !check_redirection_syntax(current, next, data))
			return (0);
		current = current->next;
	}
	return (1);
}
