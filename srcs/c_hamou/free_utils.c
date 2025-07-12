/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:22:35 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/12 03:24:11 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_all_allocations(t_command *cmd)
{
	free(cmd->args);
	free(cmd->red_in);
	free(cmd->red_out);
	free(cmd->append);
	free(cmd->heredoc_delimiters);
	free(cmd->heredoc_quotes);
}

void	cleanup(t_command *cmds, t_token *tokens, char *line)
{
	free_command(cmds);
	free_tokens(tokens);
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
