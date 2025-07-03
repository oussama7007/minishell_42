/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/03 15:11:19 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "c_spuvr/built_functions.h"
#include <readline/readline.h>
#include <readline/history.h>

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
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	main_loop(char ***my_envp, t_data *data)
{
	char		*line;
	t_token		*tokens;
	t_command	*commands;

	while (1)
	{
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
