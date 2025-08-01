/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:22:35 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/13 02:45:07 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_all_allocations(t_command *cmd)
{
	if (cmd->args)
		free(cmd->args);
	if (cmd->red_in)
		free(cmd->red_in);
	if (cmd->red_out)
		free(cmd->red_out);
	if (cmd->append)
		free(cmd->append);
	if (cmd->heredoc_delimiters)
		free(cmd->heredoc_delimiters);
	if (cmd->heredoc_quotes)
		free(cmd->heredoc_quotes);
}

void	cleanup(t_command *cmds, t_token *tokens, char *line)
{
	if (cmds)
		free_command(cmds);
	if (tokens)
		free_tokens(&tokens);
	if (line)
		free(line);
}

void	clean_accumulator(t_data *data)
{
	if (data->accumulator)
		free(data->accumulator);
	data->accumulator = NULL;
}

t_command	*build_commands(t_token **tokens, t_data *data, char **line)
{
	t_command	*commands;

	(void)line;
	if (!validate_syntax(*tokens, data))
		return (NULL);
	commands = build_command(*tokens, data);
	if (!commands)
		return (NULL);
	return (commands);
}

int	has_multiple_words(char *str)
{
	int	i;
	int	in_word;
	int	word_count;

	i = 0;
	in_word = 0;
	word_count = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
		{
			if (!in_word)
			{
				in_word = 1;
				word_count++;
			}
		}
		else
		{
			in_word = 0;
		}
		i++;
	}
	return (word_count > 1);
}
