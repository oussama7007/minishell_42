<<<<<<< HEAD
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
=======
<<<<<<< HEAD
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
// #include <stdlib.h>
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:34:06 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/29 21:57:25 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
>>>>>>> bf0e99ec959c40e207915c72f39fd029fdc72051

// char 	**function(char **arr)
// {
// 	char **aff;
// 	int len = 0;
// 	while(arr[len])
// 		len++;
// 	int i = 0;
// 	len++;
// 	aff = malloc(sizeof(char *) * len);
// 	while(arr[i])
// 	{
// 		aff[i] = strdup(arr[i]);
// 		i++;
// 	}
// 	int j = 0;
	
// 	aff[i] = strdup("morocco");
// 	aff[++i] = NULL;
// 	return aff;
// }

<<<<<<< HEAD
// int main()
// {
// 	char **arr = malloc(sizeof(char *) * 3);
// 	arr[0] = strdup("hello"); //  
// 	arr[1] = strdup("world");
// 	arr[3] = NULL;
// 	arr = function(arr);
// 	while(*arr)
// 	{
// 		printf("%s\n", *arr);
// 		arr++;
// 	}
// }
=======
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
>>>>>>> 36f2b75ef37ea107c85b8ab3c274046b952fbf11

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

<<<<<<< HEAD
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
=======
>>>>>>> bf0e99ec959c40e207915c72f39fd029fdc72051
>>>>>>> 36f2b75ef37ea107c85b8ab3c274046b952fbf11
