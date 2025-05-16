/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:20:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/12 03:07:58 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void    free_tokens(t_token *tokens)
{
    t_token *tmp;
    while(tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);
    }
}
void    free_args(t_command *command)
{
    int i;
    t_command *next;
    i = 0;
    while(command)
    {
        free(command->cmd);
        if(command->args)
        {
            while(command->args[i])
                free(command->args[i++]);
            free(command->args);
        }
        free(command->args);
        i = 0;
        if(command->red_in)
        {
            while (command->red_in[i])
                free(command->red_in[i++]);
            free(command->red_in);
        }
        i = 0;
        if(command->red_out)
        {
            while (command->red_out[i])
                free(command->red_out[i++]);
            free(command->red_out);
        }
     
        free(command->append);
        free(command->heredoc_delimiter);
        next = command->next;
        free(command);
        command = next;
    }
}