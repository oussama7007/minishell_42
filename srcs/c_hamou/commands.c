/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:22:51 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/18 16:11:59 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "header.h"

t_command *new_command(void)
{
    t_command *command = malloc(sizeof(t_command));
    if (!command)
        return (NULL);
    command->cmd = NULL;
    command->args = NULL;
    command->red_in = NULL;
    command->red_out = NULL;
    command->append = NULL;
    command->heredoc_delimiter = NULL;
    command->next = NULL;
    return (command);
}

void free_command(t_command *cmd)
{
    int i;

    if (!cmd)
        return ;
    free(cmd->cmd);
    if (cmd->args)
    {
        i = -1;
        while(cmd->args[++i])
            free(cmd->args[i]);
        free(cmd->args);
    }
    if (cmd->red_in)
    {
        i = -1;
        while(cmd->red_in[++i])
            free(cmd->red_in[i]);
        free(cmd->red_in);
    }
    if (cmd->red_out)
    {
        i = -1;
        while(cmd->red_out[++i])
            free(cmd->red_out[i]);
        free(cmd->red_out);
    }
    free(cmd->append);
    free(cmd->heredoc_delimiter);
    free_command(cmd->next);
    free(cmd);
}

static int populate_command(t_command *cmd, t_token *tokens, int arg_c, int in_c, int out_c)
{
    int i = 0, j = 0, k = 0, append_idx = 0;

    cmd->args = malloc(sizeof(char *) * (arg_c + 1));
    cmd->red_in = malloc(sizeof(char *) * (in_c + 1));
    cmd->red_out = malloc(sizeof(char *) * (out_c + 1));
    cmd->append = malloc(sizeof(int) * out_c);
    if (!cmd->args || !cmd->red_in || !cmd->red_out || (out_c && !cmd->append))
        return (0);
    while (tokens && tokens->type != TOKEN_PIPE)
    {
        if (tokens->type == TOKEN_WORD)
        {
            if (!i)
                cmd->cmd = ft_strdup(tokens->value);
            cmd->args[i++] = ft_strdup(tokens->value);
        }
        else if (tokens->type == TOKEN_RED_IN && tokens->next)
        {
            tokens = tokens->next;
            cmd->red_in[j++] = ft_strdup(tokens->value);
        }
        else if ((tokens->type == TOKEN_RED_OUT || tokens->type == TOKEN_RED_APPEND) && tokens->next)
        {
            cmd->append[append_idx] = (tokens->type == TOKEN_RED_APPEND);
            tokens = tokens->next;
            cmd->red_out[k++] = ft_strdup(tokens->value);
            append_idx++;
        }
        else if (tokens->type == TOKEN_RED_HEREDOC && tokens->next)
        {
            tokens = tokens->next;
            cmd->heredoc_delimiter = ft_strdup(tokens->value);
        }
        tokens = tokens->next;
    }
    cmd->args[i] = NULL;
    cmd->red_in[j] = NULL;
    cmd->red_out[k] = NULL;
    return (1);
}

void add_command(t_command **commands, t_command *command)
{
    t_command *tmp;

    if (!command)
        return ;
    if (!*commands)
        *commands = command;
    else
    {
        tmp = *commands;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = command;
    }
}

t_command *build_command(t_token *tokens)
{
    t_command *commands = NULL, *current = NULL;
    t_token *tmp = tokens;
    int arg_count = 0, red_in_count = 0, red_out_count = 0;

    if (tokens == NULL)
        return 0;
    while (tmp)
    {
        if (!current)
        {
            current = new_command();
            if (!current)
                return (free_command(commands), NULL);
            add_command(&commands, current);
        }
        if (tmp->type == TOKEN_WORD)
            arg_count++;
        else if (tmp->type == TOKEN_RED_IN && tmp->next) // the second condition 
            red_in_count++;
        else if ((tmp->type == TOKEN_RED_OUT || tmp->type == TOKEN_RED_APPEND) && tmp->next)  // the second condition
            red_out_count++;
        if (tmp->type == TOKEN_PIPE || !tmp->next) // the second condition 
        {
            if (arg_count || red_in_count || red_out_count)
                if (!populate_command(current, tokens, arg_count, red_in_count, red_out_count))
                    return (free_command(commands), NULL);
            current = NULL;
            arg_count = 0;
            red_in_count = 0;
            red_out_count = 0;
            tokens = tmp->next;
        }
        tmp = tmp->next;
    }
    return (commands);
}