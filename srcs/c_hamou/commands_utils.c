/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:49:05 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/02 21:57:29 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_command	*new_command(void)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->cmd = NULL;
	command->args = NULL;
	command->red_in = NULL;
	command->red_out = NULL;
	command->append = NULL;
	command->heredoc_delimiters = NULL; // Corrected
	command->heredoc_quotes = NULL;     // Corrected
	command->num_heredocs = 0;          // Corrected
	command->heredoc_tmp_file = NULL;
	command->next = NULL;
	return (command);
}

void	add_command(t_command **commands, t_command *command)
{
	t_command	*tmp;

	if (!command)
		return ;
	if (!*commands)
		*commands = command;
	else
	{
		tmp = *commands;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = command;
	}
}

int	ensure_command_exists(t_cmd_builder *builder, t_token *token)
{
	if (builder->current)
		return (1);
	builder->current = new_command();
	if (!builder->current)
		return (0);
	add_command(&builder->commands, builder->current);
	builder->tokens_start = token;
	return (1);
}
