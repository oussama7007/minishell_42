/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:49:42 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/10 13:50:02 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_spuvr/built_functions.h"

// int	is_redirection(int token_type)
// {
// 	return (token_type == TOKEN_RED_IN
// 		|| token_type == TOKEN_RED_OUT
// 		|| token_type == TOKEN_RED_APPEND
// 		|| token_type == TOKEN_RED_HEREDOC);
// }

// int	validate_syntax(t_token *tokens)
// {
// 	t_token	*current;
// 	t_token	*next;

// 	current = tokens;
// 	while (current)
// 	{
// 		next = current->next;
// 		if (current->type == TOKEN_PIPE)
// 		{
// 			if (!next || next->type == TOKEN_PIPE)
// 				return (error(ERR_SYNTAX), 0);
// 		}
// 		else if (is_redirection(current->type))
// 		{
// 			if (!next)
// 				return (error(ERR_NEWLINE), 0);
// 			if (next->type != TOKEN_WORD)
// 				return (error(ERR_SYNTAX), 0);
// 			if (current->type != TOKEN_RED_HEREDOC
// 				&& next->is_empty_after_expand
// 				&& next->quotes_type == 0)
// 				return (error(ERR_AMBIGUOS), 0);
// 		}
// 		current = current->next;
// 	}
// 	return (1);
// }

// void	perform_field_splitting(t_token **tokens)
// {
// 	t_token	**current_ptr;
// 	t_token	*token_to_process;
// 	char	**split_words;
// 	t_token	*new_tokens;
// 	t_token	*end_of_new;

// 	current_ptr = tokens;
// 	while (*current_ptr)
// 	{
// 		token_to_process = *current_ptr;
// 		if (token_to_process->is_expanded_token
// 			&& token_to_process->quotes_type == 0)
// 		{
// 			split_words = ft_split(token_to_process->value, ' ');
// 			if (split_words && split_words[0] && split_words[1])
// 			{
// 				new_tokens = create_tokens_from_split(split_words);
// 				if (new_tokens)
// 				{
// 					end_of_new = new_tokens;
// 					while (end_of_new->next)
// 						end_of_new = end_of_new->next;
// 					end_of_new->next = token_to_process->next;
// 					*current_ptr = new_tokens;
// 					token_to_process->next = NULL;
// 					free_tokens(token_to_process);
// 					current_ptr = &end_of_new->next;
// 				}
// 			}
// 			if (split_words)
// 				free_double(split_words);
// 		}
// 		if (*current_ptr)
// 			current_ptr = &(*current_ptr)->next;
// 	}
// }

// void	main_loop(char ***my_envp, t_data *data)
// {
// 	char		*line;
// 	t_token		*tokens;
// 	t_command	*commands;

// 	while (1)
// 	{
// 		if (data->accumulator)
// 		{
// 			free(data->accumulator);
// 			data->accumulator = NULL;
// 		}
// 		line = readline("Minishell$ ");
// 		if (!line)
// 		{
// 			write(1, "exit\n", 5);
// 			free_environment(*my_envp);
// 			exit(data->ex_status);
// 		}
// 		if (*line)
// 			add_history(line);
// 		if (!handle_quotes(line) || !check_invalid_char(line))
// 		{
// 			if (!handle_quotes(line))
// 				write(2, "Minishell: Quotes aren't closed\n", 33);
// 			else
// 				write(2, "Minishell: Invalid character \n", 30);
// 			free(line);
// 			continue ;
// 		}
// 		tokens = tokenize(line, *my_envp, data);
// 		if (!tokens || !*line)
// 		{
// 			if (tokens)
// 				free_tokens(tokens);
// 			free(line);
// 			continue ;
// 		}
// 		commands = build_command(tokens);
// 		if (!commands)
// 		{
// 			free_tokens(tokens);
// 			free(line);
// 			continue ;
// 		}
// 		if (!validate_syntax(tokens, data))
// 		{
// 			free_command(commands);
// 			free_tokens(tokens);
// 			free(line);
// 			continue ;
// 		}
// 		if (!handle_heredocs_before_execution(commands, *my_envp, data))
// 		{
// 			free_command(commands);
// 			free_tokens(tokens);
// 			free(line);
// 			continue ;
// 		}
// 		remove_empty_tokens(&tokens);
// 		perform_field_splitting(&tokens);
// 		free_command(commands);
// 		commands = build_command(tokens);
// 		if (!commands)
// 		{
// 			free_tokens(tokens);
// 			free(line);
// 			continue ;
// 		}
// 		data->ex_status = ft_execute_command_list(commands, tokens, my_envp, data);
// 		free_command(commands);
// 		free_tokens(tokens);
// 		free(line);
// 	}
// }

// void debug_tokens(t_token *head)
// {
//     int index = 0;
//     t_token *current = head;

//     while (current != NULL)
//     {
//         printf("Token [%d]:\n", index);
//         printf("  type: %d\n", current->type);
//         printf("  value: %s\n", current->value ? current->value : "(null)");
//         printf("  quotes_type: %d\n", current->quotes_type);
//         printf("  is_expanded_token: %d\n", current->is_expanded_token);
//         printf("  next: %p\n", (void *)current->next);
//         printf("-----------------------\n");

//         current = current->next;
//         index++;
//     }

//     if (index == 0)
//         printf("No tokens to display (list is empty).\n");
// }