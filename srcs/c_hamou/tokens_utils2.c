/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:16:02 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/22 16:54:54 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_token     *new_token(int type, char *word, int quotes_type)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if(!new)
        return (NULL);
    new->value = ft_strdup(word);
    if(!new->value)
        return (free(new), NULL); // test this line 
    new->type = type;
    new->quotes_type = quotes_type;
    new->next = NULL;
    return new;
}
int     get_token_type(char *line)
{
    if(!line || line[0])
        return(TOKEN_WORD);
    if(line[0] == '|')
        return (TOKEN_PIPE);
    if(line[0] == '<' && line[1] == '<')
        return (TOKEN_RED_HEREDOC);
    if(line[0] == '>' && line[1] == '>')
        return (TOKEN_RED_APPEND);
    if(line[0] == '<')
        return (TOKEN_RED_IN);
    if(line[0] == '>')
        return (TOKEN_RED_OUT);
    return(TOKEN_WORD);
}
void    add_token(t_token **tokens, t_token *token)
{
    t_token *tmp =  NULL;
    if(!*tokens)
        *tokens = token;
    else 
    {
        tmp = *tokens;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = token;
    }
}
char *process_segment(char **start, int *quotes_type, char **env, int ex_status)
{
    if (**start == '\'' || **start == '"')
        return handle_quoted_part(start, quotes_type, env, ex_status);
    else
        return handle_unquoted_part(start, quotes_type, env, ex_status);
}
t_token *handle_operator(char **start, int quotes_type)
{
    char *word;
    t_token *token;
    char *end = *start;

    if (*end == '<' && *(end + 1) == '<')
        end += 2;
    else if (*end == '>' && *(end + 1) == '>')
        end += 2;
    else
        end++;
    word = ft_strndup(*start, end - *start);
    if (!word)
        return (NULL);
    token = new_token(get_token_type(word), word, quotes_type);
    *start = end;
    free(word);
    return token;
}