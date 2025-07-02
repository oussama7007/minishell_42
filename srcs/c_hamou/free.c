/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:20:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/02 23:19:27 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_double(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	free_double(cmd->args);
	free_double(cmd->red_in);
	free_double(cmd->red_out);
	if (cmd->append)
		free(cmd->append);
	free_double(cmd->heredoc_delimiters);
	if (cmd->heredoc_quotes)
		free(cmd->heredoc_quotes);
	if (cmd->heredoc_tmp_file)
		free(cmd->heredoc_tmp_file);
	if (cmd->next)
		free_command(cmd->next);
	free(cmd);
}
