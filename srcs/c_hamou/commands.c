/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:22:51 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/01 22:45:47 by oait-si-         ###   ########.fr       */
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
		cmd->heredoc_delimiter = ft_strdup(token->value);
		cmd->heredoc_quotes = (token->quotes_type != 0);
		return (token->next);
	}
	return (token->next);
}

t_token	*process_token(t_token *token, t_command *cmd, t_indices *idx)
{
	if (token->type == TOKEN_WORD && token->value[0] != '\0')
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
	cmd->args = malloc(sizeof(char *) * (counts.arg_c + 1));
	cmd->red_in = malloc(sizeof(char *) * (counts.in_c + 1));
	cmd->red_out = malloc(sizeof(char *) * (counts.out_c + 1));
	cmd->append = malloc(sizeof(int) * counts.out_c);
	if (!cmd->args || !cmd->red_in || !cmd->red_out
		|| (counts.out_c && !cmd->append))
		return (0);
	while (tokens && tokens->type != TOKEN_PIPE)
		tokens = process_token(tokens, cmd, &idx);
	cmd->args[idx.i] = NULL;
	cmd->red_in[idx.j] = NULL;
	cmd->red_out[idx.k] = NULL;
	return (1);
}

int	finalize_command(t_cmd_builder *builder)
{
	t_counts	counts;

	if (!builder->current || (!builder->arg_count && !builder->red_in_count
			&& !builder->red_out_count))
	{
		builder->current = NULL;
		return (1);
	}
	counts.arg_c = builder->arg_count;
	counts.in_c = builder->red_in_count;
	counts.out_c = builder->red_out_count;
	if (!populate_command(builder->current, builder->tokens_start, counts))
		return (0);
	builder->current = NULL;
	builder->arg_count = 0;
	builder->red_in_count = 0;
	builder->red_out_count = 0;
	return (1);
}

t_command	*build_command(t_token *tokens)
{
	t_cmd_builder	builder;

	builder = (t_cmd_builder){0};
	if (!tokens)
		return (NULL);
	while (tokens)
	{
		if (!ensure_command_exists(&builder, tokens))
			return (free_command(builder.commands), NULL);
		if (tokens->type == TOKEN_WORD)
			builder.arg_count++;
		else if (tokens->type == TOKEN_RED_IN && tokens->next)
			builder.red_in_count++;
		else if ((tokens->type == TOKEN_RED_OUT
				|| tokens->type == TOKEN_RED_APPEND) && tokens->next)
			builder.red_out_count++;
		if (tokens->type == TOKEN_PIPE || !tokens->next)
			if (!finalize_command(&builder))
				return (free_command(builder.commands), NULL);
		tokens = tokens->next;
	}
	return (builder.commands);
}
