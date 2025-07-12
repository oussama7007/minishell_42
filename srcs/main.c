/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/12 17:30:29 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_spuvr/built_functions.h"

void	perform_field_splitting(t_token **tokens)
{
	t_token	**current_ptr;
	t_token	*original_token;

	current_ptr = tokens;
	while (*current_ptr)
	{
		original_token = *current_ptr;
		process_token_split(current_ptr);
		if (*current_ptr == original_token)
			current_ptr = &(*current_ptr)->next;
	}
}

int	execute_commands(t_command **cmds, t_token **tokens,
		char ***env, t_data *data)
{
	remove_empty_tokens(tokens);
	perform_field_splitting(tokens);
	if (!prepare_execution(cmds, tokens, env, data))
		return (0);
	data->ex_status = ft_execute_command_list(*cmds, *tokens, env, data);
	return (1);
}

int	process_input(char **line, t_data *data)
{
	int	quote_error;

	quote_error = !handle_quotes(*line);
	if (quote_error || !check_invalid_char(*line))
	{
		if (quote_error)
			write(2, "Minishell: Quotes aren't closed\n", 33);
		else
			write(2, "Minishell: Invalid character\n", 29);
		data->ex_status = 2;
		free(*line);
		return (0);
	}
	return (1);
}

void	main_loop(char ***my_envp, t_data *data)
{
	char		*line;
	t_token		*tokens;
	t_command	*commands;

	while (1)
	{
		commands = NULL;
		tokens = NULL;
		line = NULL;
		clean_accumulator(data);
		line = readline("Minishell$ ");
		if (handle_exit(line, my_envp, data))
			break ;
		if (*line)
			add_history(line);
		if (!process_input(&line, data))
			continue ;
		tokens = tokenize(line, *my_envp, data);
		if (tokens && validate_tokens(&tokens, data, &line))
		{
			commands = build_commands(&tokens, data, &line);
			if (commands)
				execute_commands(&commands, &tokens, my_envp, data);
		}
		cleanup(commands, tokens, line);
	}
}

int	main(int ac, char **av, char **env)
{
	char	**my_envp;
	t_data	data;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		exit(1);
	data = (t_data){0};
	(void)ac;
	(void)av;
	my_envp = init_environment(env);
	ensure_minimal_env(&my_envp);
	setup_signal_handlers();
	exit_status(0, 0, &data);
	main_loop(&my_envp, &data);
	free_environment(my_envp);
	return (data.ex_status);
}
