/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:49:42 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/12 02:15:44 by oait-si-         ###   ########.fr       */
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
int	check_pipe_syntax(t_token *current, t_token *next, t_data *data)
{
	if (current->type == TOKEN_PIPE)
	{
		if (!next || next->type == TOKEN_PIPE)
			return (error(ERR_SYNTAX), data->ex_status = 2, 0);
	}
	return (1);
}

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


void	exit_status(int set, int value, t_data *data)
{
	
	static t_data *hh;
	
	if (data)
		hh = data;
	if (set)
		hh->ex_status = value;
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	should_split_token(t_token *token)
{
	return (token->is_expanded_token
		&& token->quotes_type == 0
		&& !token->is_assigning_expand_token);
}

void	replace_token(t_token **current_ptr, t_token *token_to_process,
			char **split_words)
{
	t_token	*new_tokens;
	t_token	*end_of_new;

	new_tokens = create_tokens_from_split(split_words);
	if (new_tokens)
	{
		end_of_new = new_tokens;
		while (end_of_new->next)
			end_of_new = end_of_new->next;
		end_of_new->next = token_to_process->next;
		*current_ptr = new_tokens;
		token_to_process->next = NULL;
		free_tokens(token_to_process);
		*current_ptr = end_of_new;
	}
}

void	process_token_split(t_token **current_ptr)
{
	t_token	*token_to_process;
	char	**split_words;

	token_to_process = *current_ptr;
	if (should_split_token(token_to_process))
	{
		split_words = ft_split(token_to_process->value, ' ');
		if (split_words && split_words[0] && split_words[1])
			replace_token(current_ptr, token_to_process, split_words);
		if (split_words)
			free_double(split_words);
	}
}

void	perform_field_splitting(t_token **tokens)
{
	t_token	**current_ptr;

	current_ptr = tokens;
	while (*current_ptr)
	{
		process_token_split(current_ptr);
		if (*current_ptr)
			current_ptr = &(*current_ptr)->next;
	}
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


int	validate_tokens(t_token **tokens, t_data *data, char **line)
{
	if (!*tokens || !**line)
	{
		if (*tokens)
			free_tokens(*tokens);
		free(*line);
		return (0);
	}
	if ((*tokens)->type == T_PIPE)
	{
		error(ERR_PIPE);
		free_tokens(*tokens);
		free(*line);
		data->ex_status = 2;
		return (0);
	}
	return (1);
}

t_command	*build_commands(t_token **tokens, t_data *data, char **line)
{
	t_command	*commands;

	commands = build_command(*tokens);
	if (!commands || !validate_syntax(*tokens, data))
	{
		if (commands)
			free_command(commands);
		free_tokens(*tokens);
		free(*line);
		return (NULL);
	}
	return (commands);
}

int	prepare_execution(t_command **cmds, t_token **tokens,
			char ***env, t_data *data)
{
	free_command(*cmds);
	*cmds = build_command(*tokens);
	if (!*cmds)
	{
		free_tokens(*tokens);
		return (0);
	}
	if (!handle_heredocs_before_execution(*cmds, *env, data))
	{
		free_command(*cmds);
		free_tokens(*tokens);
		return (0);
	}
	return (1);
}



