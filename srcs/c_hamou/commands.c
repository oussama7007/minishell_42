/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:22:51 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/13 03:19:53 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_token	*process_token(t_token *token, t_command *cmd, t_indices *idx)
{
	if (token->type == TOKEN_WORD)
	{
		if (!cmd->cmd)
			cmd->cmd = ft_strdup(token->value);
		cmd->args[idx->i++] = ft_strdup(token->value);
		return (token->next);
	}
	return (handle_redirection(token, cmd, idx));
}

int	populate_command(t_command *cmd, t_token *tokens, t_counts counts)
{
	t_indices	idx;

	idx = (t_indices){0};
	if (!allocate_memory(cmd, counts))
		return (0);
	while (tokens && tokens->type != TOKEN_PIPE)
		tokens = process_token(tokens, cmd, &idx);
	terminate_arrays(cmd, &idx, counts);
	return (1);
}

int	should_skip_empty_command(t_cmd_builder *builder, t_token *first_word_token)
{
	if (builder->arg_count == 1 && builder->red_in_count == 0
		&& builder->red_out_count == 0 && builder->heredoc_count == 0
		&& first_word_token && first_word_token->is_empty_after_expand)
	{
		builder->current = NULL;
		builder->arg_count = 0;
		return (1);
	}
	return (0);
}

int	finalize_command(t_cmd_builder *builder)
{
	t_counts	counts;
	t_token		*first_word_token;

	if (!builder->current || (!builder->arg_count && !builder->red_in_count
			&& !builder->red_out_count && !builder->heredoc_count))
	{
		builder->current = NULL;
		return (1);
	}
	first_word_token = builder->tokens_start;
	while (first_word_token && first_word_token->type != TOKEN_PIPE)
	{
		if (first_word_token->type == TOKEN_WORD)
			break ;
		first_word_token = first_word_token->next;
	}
	if (should_skip_empty_command(builder, first_word_token))
		return (1);
	init_counts(&counts, builder);
	if (!populate_command(builder->current, builder->tokens_start, counts))
		return (0);
	terminate_arr_finalize_command(builder);
	return (1);
}

t_command	*build_command(t_token *tokens, t_data *data)
{
	t_cmd_builder	builder;
	int				total_heredoc_count;

	builder = (t_cmd_builder){0};
	total_heredoc_count = 0;
	if (!tokens)
		return (NULL);
	while (tokens)
	{
		if (!ensure_command_exists(&builder, tokens))
			return (free_command(builder.commands), NULL);
		if (!process_tokens(&builder, tokens, data, &total_heredoc_count))
			return (free_command(builder.commands), NULL);
		if (tokens->type == TOKEN_PIPE || !tokens->next)
		{
			if (!finalize_command(&builder))
				return (free_command(builder.commands), NULL);
		}
		tokens = tokens->next;
	}
	return (builder.commands);
}
