typedef struct s_indices
{
	int	i;
	int	j;
	int	k;
	int	append_idx;
}	t_indices;

static t_token	*process_token(t_token *token, t_command *cmd, t_indices *idx)
{
	if (token->type == TOKEN_WORD && token->value[0] != '\0')
	{
		if (!cmd->cmd)
			cmd->cmd = ft_strdup(token->value);
		cmd->args[idx->i++] = ft_strdup(token->value);
		return (token->next);
	}
	else if (token->type == TOKEN_RED_IN && token->next)
	{
		token = token->next;
		cmd->red_in[idx->j++] = ft_strdup(token->value);
		return (token->next);
	}
	else if ((token->type == TOKEN_RED_OUT || token->type == TOKEN_RED_APPEND)
		&& token->next)
	{
		cmd->append[idx->append_idx++] = (token->type == TOKEN_RED_APPEND);
		token = token->next;
		cmd->red_out[idx->k++] = ft_strdup(token->value);
		return (token->next);
	}
	else if (token->type == TOKEN_RED_HEREDOC && token->next)
	{
		token = token->next;
		cmd->heredoc_delimiter = ft_strdup(token->value);
		cmd->heredoc_quotes = (token->quotes_type != 0);
		return (token->next);
	}
	return (token->next);
}

static int	populate_command(t_command *cmd, t_token *tokens,
				int arg_c, int in_c, int out_c)
{
	t_indices	idx;

	idx = (t_indices){0};
	cmd->args = malloc(sizeof(char *) * (arg_c + 1));
	cmd->red_in = malloc(sizeof(char *) * (in_c + 1));
	cmd->red_out = malloc(sizeof(char *) * (out_c + 1));
	cmd->append = malloc(sizeof(int) * out_c);
	if (!cmd->args || !cmd->red_in || !cmd->red_out || (out_c && !cmd->append))
		return (0);
	while (tokens && tokens->type != TOKEN_PIPE)
		tokens = process_token(tokens, cmd, &idx);
	cmd->args[idx.i] = NULL;
	cmd->red_in[idx.j] = NULL;
	cmd->red_out[idx.k] = NULL;
	return (1);
}