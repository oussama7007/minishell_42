/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:49:42 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/11 22:00:48 by oait-si-         ###   ########.fr       */
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
int	validate_syntax(t_token *tokens,t_data *data)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
		while (current)
	{
		next = current->next;
		if (current->type == TOKEN_PIPE)
		{
			if (!next || next->type == TOKEN_PIPE)
			{
				error(ERR_SYNTAX);
				data->ex_status = 2;
				return (0);
			}
		}
		else if (is_redirection(current->type))
		{
			if (!next)
			{
				data->ex_status = 2;
				error(ERR_NEWLINE);
				return (0);
            }
			if (next->type != TOKEN_WORD)
			{
				data->ex_status = 2;
				error(ERR_SYNTAX);
				return (0);
			}
            if ((current->type != TOKEN_RED_HEREDOC && next->is_empty_after_expand && next->quotes_type == 0) 
				|| next->has_whit_space)
			{
				error(ERR_AMBIGUOS);
				data->ex_status = 1;
				return (0);
			}
			
		}
		current = current->next;
	}
		
	
	return (1);
}
void	exit_status(int set, int value, t_data *data)
{
	static int l;
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

void	perform_field_splitting(t_token **tokens)
{
	t_token	**current_ptr;
	t_token	*token_to_process;
	char	**split_words;

	current_ptr = tokens;
	while (*current_ptr)
	{
		token_to_process = *current_ptr;
	
		if (token_to_process->is_expanded_token
			&& token_to_process->quotes_type == 0 && !token_to_process->is_assigning_expand_token)
		{
			split_words = ft_split(token_to_process->value, ' ');
		
			if (split_words && split_words[0] && split_words[1])
			{
				t_token *new_tokens = create_tokens_from_split(split_words);
				if (new_tokens)
				{
					t_token *end_of_new = new_tokens;
					while (end_of_new->next)
						end_of_new = end_of_new->next;
					end_of_new->next = token_to_process->next;
					*current_ptr = new_tokens;
					token_to_process->next = NULL;
					free_tokens(token_to_process);
					current_ptr = &end_of_new->next;
				}
			}
			if (split_words)
				free_double(split_words);
		}
		if (*current_ptr)
			current_ptr = &(*current_ptr)->next;
	}
}
void	main_loop(char ***my_envp, t_data *data)
{
	char		*line;
	t_token		*tokens;
	t_command	*commands;

	setup_signal_handlers();
	exit_status(0, 0, data);
	while (1)
	{
		if(data->accumulator)
		{
			free(data->accumulator);
			data->accumulator = NULL;
		}
		line = readline("Minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			free_environment(*my_envp);
			exit(data->ex_status);
		}
		if (*line)
			add_history(line);
		if (!handle_quotes(line) || !check_invalid_char(line))
		{
			if (!handle_quotes(line))
			{
				data->ex_status = 2;
				write(2, "Minishell: Quotes aren't closed\n", 33);
			}
			else
			{
				data->ex_status = 2;
				write(2, "Minishell: Invalid character \n", 30);
			}
			free(line);
			continue ;
		}
		tokens = tokenize(line, *my_envp, data);
		if (!tokens || !*line)
		{
			if (tokens)
				free_tokens(tokens);
			free(line);
			continue ;
		}
		if(tokens && tokens->type == T_PIPE)
		{
			error(ERR_PIPE);
			free_tokens(tokens);
			free(line);
			data->ex_status = 2;
			continue;
		}

		commands = build_command(tokens);
		if (!commands)
		{	
			free_tokens(tokens);
			free(line);
			continue;
		}
        if (!validate_syntax(tokens, data))
		{
			free_command(commands);
			free_tokens(tokens);
			free(line);
			continue;
		}
		remove_empty_tokens(&tokens);
        
		perform_field_splitting(&tokens);
		free_command(commands);
		commands = build_command(tokens);
		if (!commands)
		{
			free_tokens(tokens);
			free(line);
			continue;
		}
		if (!handle_heredocs_before_execution(commands, *my_envp, data))
		{
			free_command(commands);
			free_tokens(tokens);
			free(line);
			continue ;
		}
		
		data->ex_status = ft_execute_command_list(commands, tokens, my_envp, data);
		free_command(commands);
		free_tokens(tokens);
		free(line);
	}
}

