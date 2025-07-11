/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:49:37 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/11 23:24:02 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_token	*handle_redirection(t_token *token, t_command *cmd, t_indices *idx)
{
	if (token->type == TOKEN_RED_IN && token->next)
	{
		token = token->next;
		cmd->red_in[idx->j++] = ft_strdup(token->value);
		return (token->next);
	}
	if ((token->type == TOKEN_RED_OUT || token->type == TOKEN_RED_APPEND)
		&& token->next)
	{
		cmd->append[idx->append_idx++] = (token->type == TOKEN_RED_APPEND);
		token = token->next;
		cmd->red_out[idx->k++] = ft_strdup(token->value);
		return (token->next);
	}
	if (token->type == TOKEN_RED_HEREDOC && token->next)
	{
		token = token->next;
		cmd->heredoc_delimiters[idx->heredoc_idx] = ft_strdup(token->value);
		cmd->heredoc_quotes[idx->heredoc_idx] = (token->quotes_type != 0);
		idx->heredoc_idx++;
		return (token->next);
	}
	return (token->next);
}

void	terminate_arr_finalize_command(t_cmd_builder *builder)
{
	builder->current = NULL;
	builder->arg_count = 0;
	builder->red_in_count = 0;
	builder->red_out_count = 0;
	builder->heredoc_count = 0;
}

void	init_counts(t_counts *counts, t_cmd_builder *builder)
{
	counts->arg_c = builder->arg_count;
	counts->in_c = builder->red_in_count;
	counts->out_c = builder->red_out_count;
	counts->heredoc_c = builder->heredoc_count;
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
	cmd->heredoc_delimiters = NULL;
	cmd->heredoc_quotes = NULL;
	if (!allocate_primary_memory(cmd, counts))
	{
		free_all_allocations(cmd);
		return (0);
	}
	if (!allocate_heredoc_memory(cmd, counts.heredoc_c))
	{
		free_all_allocations(cmd);
		return (0);
	}
	return (1);
}
