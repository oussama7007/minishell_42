/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:22:51 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/12 02:23:51 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

// int     add_args(t_token  *token, t_command *command)
// {
    
// }

int     assigne_values(t_command *command, t_token *token)
{
    if(token->type == 0)
    {
        command->cmd = ft_strdup(token->value);
        command->args[0] = ft_strdup(token->value);
        if(!command->cmd || !command->args[0])
            return 0;
        if(token->next->type == 0)
        {
            command->args[1] = ft_strdup(token->next->type);
            command->args[2] = NULL;
            if(!command->args[1])
                return 0;
        }
        else 
            command->args[1] = NULL;
    }
    if(token->type == )
}
t_command      *new_command(t_token *token)
{
    t_command *command;

    command = malloc(sizeof(t_command));
    if(!command)
        return(NULL);
    if(!assigne_values(command, token))
        return(NULL);
    return command;
}
t_command     build_command(t_token *token)
{
    t_command *commands;
    t_command *command;
    command = NULL;
    while(token)
    {
        command = new_command(token);
    } 
}