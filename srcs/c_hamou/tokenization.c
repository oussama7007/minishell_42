/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:12:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/01 15:48:12 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_token *tokenize(char *line)
{
    t_token *tokens = NULL;
    char    *start = line;
    char    *end;
    char    *word;
    t_token *token;
    char    *accumulator = NULL;
    char    *tmp;
    char quote_type;
    int quotes_type = 0 ;
    
    while (*start) 
    {
        // Skip leading spaces
        while (*start && (*start == ' ' || *start == '\t'))
            start++;
        // Check if it's an operator
        if (*start && (*start == '|'  || *start == '<' || *start == '>'))
        {
            end = start;
            if (*start && (*start == '<' && *(start + 1) == '<'))
                end += 2;
            else if (*start && (*start == '>' && *(start + 1) == '>'))
                end += 2;
            else
                end++;
            word = ft_strndup(start, end - start);
            if (!word)
                return free_tokens(tokens), NULL;
            token = new_token(get_token_type(word), word, quotes_type);
            free(word);
            if (!token)
                return free_tokens(tokens), NULL;
            add_token(&tokens, token);
            start = end;
        }
        else
        {
            // Accumulate a word (unquoted + quoted parts)
            accumulator = NULL;
            while (*start && *start != ' ' && *start != '\t' &&
                   *start != '|' && *start != '<' && *start != '>')
            {
                if (*start && (*start == '\'' || *start == '"')) // Handle quoted string
                {
                    quote_type = *start;
                    if(*start && quote_type == '"')
                        quotes_type = 2;
                    else 
                        quotes_type = 1; 
                    start++; // Skip opening quote
                    end = start;
                    while (*end && *end != quote_type)
                        end++;
                    
                    // if (*end != quote_type)
                    // {
                    //     write(2, "minishell: syntax error: unmatched quote\n", 40);
                    //     free(accumulator);
                    //     free_tokens(tokens);
                    //     return NULL;
                    // }
                    word = ft_strndup(start, end - start);
                    if (!word)
                    {
                        free(accumulator);
                        free_tokens(tokens);
                        return NULL;
                    }
                    tmp = accumulator;
                    accumulator = ft_strjoin(tmp, word);
                    free(tmp);
                    free(word);
                    if (!accumulator)
                    {
                        free_tokens(tokens);
                        return NULL;
                    }
                    start = end + 1; // Skip closing quote
                }
                else
                {
                    quotes_type = 0;
                    // Handle unquoted part
                    end = start;
                    while (*end && *end != ' ' && *end != '\t' &&
                           *end != '|' && *end != '<' && *end != '>' &&
                           *end != '\'' && *end != '"')
                        end++;
                    word = ft_strndup(start, end - start);
                    if (!word)
                    {
                        free(accumulator);
                        free_tokens(tokens);
                        return NULL;
                    }
                    tmp = accumulator;
                    accumulator = ft_strjoin(tmp, word);
                    free(tmp);
                    free(word);
                    if (!accumulator)
                    {
                        free_tokens(tokens);
                        return NULL;
                    }
                    start = end;
                }
                
            }
            if (accumulator)
            {
                token = new_token(get_token_type(accumulator), accumulator, quotes_type);
                free(accumulator);
                if (!token)
                {
                    free_tokens(tokens);
                    return NULL;
                }
                add_token(&tokens, token);
            }
        }
        
    }
    return tokens;
}
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

