/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/06 21:15:09 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "c_spuvr/built_functions.h"
#include <readline/readline.h>
#include <readline/history.h>


void debug_tokens(t_token *head)
{
    int index = 0;
    t_token *current = head;

    while (current != NULL)
    {
        printf("Token [%d]:\n", index);
        printf("  type: %d\n", current->type);
        printf("  value: %s\n", current->value ? current->value : "(null)");
        printf("  quotes_type: %d\n", current->quotes_type);
        printf("  is_expanded_token: %d\n", current->is_expanded_token);
        printf("  next: %p\n", (void *)current->next);
        printf("-----------------------\n");

        current = current->next;
        index++;
    }

    if (index == 0)
        printf("No tokens to display (list is empty).\n");
}
void	error(int type)
{
	if (type == ERR_PIPE)
		write(2, "Minishell: syntax error near unexpected token `|'\n", 50);
	else if (type == ERR_SEMICOLON)
		write(2, "Minishell: syntax error near unexpected token `;'\n", 51);
	else if (type == ERR_NEWLINE)
		write(2, "Minishell: syntax error near unexpected token `newline'\n", 57);
	else if (type == ERR_SYNTAX)
		write(2, "Minishell: syntax error \n", 26);
	else
		write(2, "Minishell: syntax error \n", 26);
}

static int	is_redirection(int token_type)
{
	return (token_type == TOKEN_RED_IN
		|| token_type == TOKEN_RED_OUT
		|| token_type == TOKEN_RED_APPEND
		|| token_type == TOKEN_RED_HEREDOC);
}

int	validate_syntax(t_token *tokens)
{
	int		type;
	t_token	*next;

	while (tokens)
	{
		type = tokens->type;
		next = tokens->next;
		if (type == TOKEN_PIPE)
		{
			if (!next)
				return (error(ERR_NEWLINE), 0);
			if (next->type == TOKEN_PIPE)
				return (error(ERR_SYNTAX), 0);
		}
		else if (is_redirection(type))
		{
			if (!next || next->type != TOKEN_WORD)
				return (error(ERR_SYNTAX), 0);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	check_single_quotes(char *line, int *i)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == '\'')
			return (1);
		(*i)++;
	}
	return (0);
}

int	check_double_quotes(char *line, int *i)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == '"')
			return (1);
		(*i)++;
	}
	return (0);
}

int	handle_quotes(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			if (!check_single_quotes(line, &i))
				return (0);
		}
		if (line[i] == '"')
		{
			if (!check_double_quotes(line, &i))
				return (0);
		}
	}
	return (1);
}

int	check_invalid_char(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ';' || line[i] == 92)
			return (0);
	}
	return (1);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
static t_token	*create_tokens_from_split(char **split_words)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	if (!split_words || !split_words[0])
		return (NULL);
	while (split_words[i])
	{
		// Each new word is a simple WORD token.
		// It's not quoted and the expansion has already been done.
		add_token(&head, new_token(T_WORD, split_words[i], 0, 0));
		i++;
	}
	return (head);
}

/**
 * @brief Iterates through the token list and performs field splitting on
 * unquoted, expanded variables.
 * @param tokens A pointer to the head of the token list. The list is modified
 * in place.
 */
void	perform_field_splitting(t_token **tokens)
{
	t_token	**current_ptr;
	t_token	*token_to_process;
	char	**split_words;

	current_ptr = tokens;
	while (*current_ptr)
	{
		token_to_process = *current_ptr;
		// This is the crucial condition for field splitting
		if (token_to_process->is_expanded_token
			&& token_to_process->quotes_type == 0)
		{
			split_words = ft_split(token_to_process->value, ' ');
			// Only split if there is more than one resulting word
			if (split_words && split_words[0] && split_words[1])
			{
				t_token *new_tokens = create_tokens_from_split(split_words);
				if (new_tokens)
				{
					// Find the end of the newly created list
					t_token *end_of_new = new_tokens;
					while (end_of_new->next)
						end_of_new = end_of_new->next;
					
					// Link the end of the new list to the rest of the original list
					end_of_new->next = token_to_process->next;
					
					// Replace the old token with the new list of tokens
					*current_ptr = new_tokens;
					
					// Free the original token (decouple it first)
					token_to_process->next = NULL;
					free_tokens(token_to_process);
					
					// Move the main pointer to the end of the newly inserted list
					// to avoid re-processing the same tokens.
					current_ptr = &end_of_new->next;
				}
			}
			if (split_words)
				free_double(split_words); // Always free the split array
		}
		// If no splitting happened, just move to the next token
		if (*current_ptr)
			current_ptr = &(*current_ptr)->next;
	}
}

static void	main_loop(char ***my_envp, t_data *data)
{
	char		*line;
	t_token		*tokens;
	t_command	*commands;
	t_token *final_tokens;
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
				write(2, "Minishell: Quotes aren't closed\n", 33);
			else
				write(2, "Minishell: Invalid character \n", 30);
			free(line);
			continue ;
		}
		tokens = tokenize(line, *my_envp, data);
		if (!tokens || !*line || !validate_syntax(tokens))
		{
			if (tokens)
				free_tokens(tokens);
			free(line);
			continue ;
		}
		perform_field_splitting(&tokens);
		debug_tokens(tokens);
		commands = build_command(tokens);
		if (commands)
		{
			if (!handle_heredocs_before_execution(commands, *my_envp, data))
			{
				free_command(commands);
				free_tokens(tokens);
				free(line);
				continue ;
			}
			if (commands->cmd && ft_strcmp(commands->cmd, "exit") == 0)
				data->ex_status = ft_exit(commands->args, my_envp, commands,
						tokens, data);
			else
				data->ex_status = ft_execute_command_list(commands, my_envp,
						data);
			free_command(commands);
		}
		free_tokens(tokens);
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	char	**my_envp;
	t_data	data;
   
	(void)ac;
	setup_signal_handlers();
	my_envp = init_environment(env);
	ensure_minimal_env(&my_envp);
	my_setenv("_", av[0], &my_envp);
	data = (t_data){0};
	main_loop(&my_envp, &data);
	free_environment(my_envp);
	return (data.ex_status);
}
