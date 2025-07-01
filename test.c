static int	add_word_token(t_command *cmd, t_token **tokens, int *i)
{
	if ((*tokens)->type == TOKEN_WORD && (*tokens)->value[0] != '\0')
	{
		if (cmd->cmd == NULL)
			cmd->cmd = ft_strdup((*tokens)->value);
		cmd->args[(*i)++] = ft_strdup((*tokens)->value);
		return (1);
	}
	return (0);
}

static int	add_red_in_token(t_command *cmd, t_token **tokens, int *j)
{
	if ((*tokens)->type == TOKEN_RED_IN && (*tokens)->next)
	{
		cmd->red_in[(*j)++] = ft_strdup(((*tokens) = (*tokens)->next)->value);
		return (1);
	}
	return (0);
}

static int	add_red_out_token(t_command *cmd, t_token **tokens, int *k,
				int *append_idx)
{
	if (((*tokens)->type == TOKEN_RED_OUT || (*tokens)->type == TOKEN_RED_APPEND)
		&& (*tokens)->next)
	{
		cmd->append[*append_idx] = ((*tokens)->type == TOKEN_RED_APPEND);
		cmd->red_out[(*k)++] = ft_strdup(((*tokens) = (*tokens)->next)->value);
		(*append_idx)++;
		return (1);
	}
	return (0);
}

static int	add_heredoc_token(t_command *cmd, t_token **tokens)
{
	if ((*tokens)->type == TOKEN_RED_HEREDOC && (*tokens)->next)
	{
		*tokens = (*tokens)->next;
		cmd->heredoc_delimiter = ft_strdup((*tokens)->value);
		cmd->heredoc_quotes = ((*tokens)->quotes_type != 0);
		return (1);
	}
	return (0);
}

static int	populate_command(t_command *cmd, t_token *tokens,
				int arg_c, int in_c, int out_c)
{
	int	i;
	int	j;
	int	k;
	int	append_idx;

	i = 0;
	j = 0;
	k = 0;
	append_idx = 0;
	cmd->args = malloc(sizeof(char *) * (arg_c + 1));
	cmd->red_in = malloc(sizeof(char *) * (in_c + 1));
	cmd->red_out = malloc(sizeof(char *) * (out_c + 1));
	cmd->append = malloc(sizeof(int) * out_c);
	if (!cmd->args || !cmd->red_in || !cmd->red_out
		|| (out_c && !cmd->append))
		return (0);
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (add_word_token(cmd, &tokens, &i) == 0
			&& add_red_in_token(cmd, &tokens, &j) == 0
			&& add_red_out_token(cmd, &tokens, &k, &append_idx) == 0
			&& add_heredoc_token(cmd, &tokens) == 0)
			tokens = tokens->next;
	}
	cmd->args[i] = NULL;
	cmd->red_in[j] = NULL;
	cmd->red_out[k] = NULL;
	return (1);
}
