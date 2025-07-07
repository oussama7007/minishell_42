/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:49:05 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/07 10:35:45 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_command	*new_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->cmd = NULL;
	command->args = NULL;
	command->red_in = NULL;
	command->red_out = NULL;
	command->append = NULL;
	command->heredoc_delimiters = NULL;
	command->heredoc_quotes = NULL;
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

void	terminate_arrays(t_command *cmd, t_indices *idx, t_counts counts)
{
	cmd->args[idx->i] = NULL;
	cmd->red_in[idx->j] = NULL;
	cmd->red_out[idx->k] = NULL;
	if (counts.heredoc_c > 0)
		cmd->heredoc_delimiters[idx->heredoc_idx] = NULL;
}

int	allocate_memory(t_command *cmd, t_counts counts)
{
	cmd->cmd = NULL;
	cmd->num_heredocs = counts.heredoc_c;
	if (counts.heredoc_c > 0)
	{
		cmd->heredoc_delimiters
			= malloc(sizeof(char *) * (counts.heredoc_c + 1));
		cmd->heredoc_quotes = malloc(sizeof(int) * counts.heredoc_c);
	}
	cmd->args = malloc(sizeof(char *) * (counts.arg_c + 1));
	cmd->red_in = malloc(sizeof(char *) * (counts.in_c + 1));
	cmd->red_out = malloc(sizeof(char *) * (counts.out_c + 1));
	cmd->append = malloc(sizeof(int) * counts.out_c);
	if (!cmd->args || !cmd->red_in || !cmd->red_out
		|| (counts.out_c > 0 && !cmd->append)
		|| (counts.heredoc_c > 0 && (!cmd->heredoc_delimiters
				|| !cmd->heredoc_quotes)))
		return (0);
	return (1);
}
