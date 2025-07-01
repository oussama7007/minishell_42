/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:20:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/01 17:06:09 by oait-si-         ###   ########.fr       */
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

// void	free_double(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// }

// void	free_args(t_command *command)
// {
// 	if (command->cmd)
// 		free(command->cmd);
// 	if (command->args)
// 		free_double(command->args);
// 	if (command->red_in)
// 		free_double(command->red_in);
// 	if (command->red_out)
// 		free_double(command->red_out);
// 	if (command->append)
// 		free(command->append);
// 	if (command->heredoc_delimiter)
// 		free(command->heredoc_delimiter);
// }

// void	free_command(t_command *command)
// {
// 	t_command	*next;

// 	while (command)
// 	{
// 		next = command->next;
// 		free_command(command);
// 		free(command);
// 		command = next;
// 	}
// }

void free_command(t_command *cmd)
{
    int i;

    if (!cmd)
        return;
    if (cmd->cmd)
        free(cmd->cmd);
    if (cmd->args)
    {
        i = -1;
        while (cmd->args[++i])
            free(cmd->args[i]);
        free(cmd->args);
    }
    if (cmd->red_in)
    {
        i = -1;
        while (cmd->red_in[++i])
            free(cmd->red_in[i]);
        free(cmd->red_in);
    }
    if (cmd->red_out)
    {
        i = -1;
        while (cmd->red_out[++i])
            free(cmd->red_out[i]);
        free(cmd->red_out);
    }
    if (cmd->append)
        free(cmd->append);
    if (cmd->heredoc_delimiter)
        free(cmd->heredoc_delimiter);
    free_command(cmd->next);
    free(cmd);
}