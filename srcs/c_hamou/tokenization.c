/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:12:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/20 18:20:22 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// t_token     *tokenize(char *line)
// {
//     t_token *token = NULL;
//     char    *start;
//     char    *end;
//     char *word;
//     t_token *tokens = NULL;
//     char    *accumulator = NULL; // To merge consecutive quoted strings
//     char    quote_type;
//     char *tmp;
    
    
//     start = line;
//     while(*start)
//     {
//         while(*start == ' ' && *start != '\'' && *start != '"')
//             start++;
//         if(!*start)
//             break;
//         end = start;
//         if(*start == '\'' || *start == '"')
//         {
//             accumulator = NULL;
//             quote_type = *start;
//             while(1)
//             {    
//                 start++;
//                 end = start;
//                 while(*end && *end != quote_type)
//                     end++;
//                 if (!*end)
//                     break; 
//                 word = ft_strndup(start, end - start);
//                 if(!word)
//                     return(free(accumulator), free_tokens(tokens), NULL);// test it;
//                 tmp = accumulator;
//                 accumulator = ft_strjoin(tmp ? tmp : "", word);
//                 free(tmp);
//                 free(word);
             
//                 if(!accumulator)
//                     return (free_tokens(tokens), NULL);
//                 start = end + 1;
//                 if (*start != quote_type)
//                     break;
//             }
//         }
//         if(*start == '|' || *start == ';' || *start == '<' || *start == '>')
//         {
//             if(*start == '<' && *(start + 1) == '<')
//                 end +=2;
//             else if(*start == '>' && *(start + 1) == '>')
//                 end +=2;
//             else
//                 end++;
//         }
//         else
//             while(*end && *end != '|' && *end != ';' && *end != '<' && *end != ' ' && *end != '>')
//                 end++;
//         if(end > start)
//         {
//             word = ft_strndup(start, end - start);
//             if(!word)
//                 return(free_tokens(tokens),NULL);
//             token = new_token(get_token_type(word), word);
//             free(word);
//             if(!token)  
//                 return(free_tokens(tokens), NULL);
//             add_token(&tokens, token);
//         }
//         start = end;
//     }
//     return(tokens);
// }


t_token *tokenize(char *line)
{
    t_token *tokens = NULL;
    char    *start = line;
    char    *end;
    char    *word;
    t_token *token;
    char    *accumulator = NULL;
    char    quote_type;
    char    *tmp;

    while (*start)
    {
        while (*start == ' ')
            start++; // Skip spaces
        if (!*start)
            break;
        end = start;
        if (*start == '\'' || *start == '"')
        {
            accumulator = NULL;
            quote_type = *start;
            while (*start == quote_type) // Handle consecutive quotes
            {
                start++; // Skip opening quote
                end = start;
                while (*end && *end != quote_type)
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
                start = end + 1; // Move past closing quote
            }
            // Create token from accumulated string
            if (accumulator)
            {
                token = new_token(TOKEN_WORD, accumulator);
                free(accumulator);
                if (!token)
                {
                    free_tokens(tokens);
                    return NULL;
                }
                add_token(&tokens, token);
            }
            continue; // Skip to next iteration
        }
        // Handle operators
        if (*start == '|' || *start == ';' || *start == '<' || *start == '>')
        {
            if (*start == '<' && *(start + 1) == '<')
                end += 2;
            else if (*start == '>' && *(start + 1) == '>')
                end += 2;
            else
                end++;
        }
        else // Handle unquoted words
        {
            while (*end && *end != ' ' && *end != '|' && *end != ';' && *end != '<' && *end != '>' && *end != '\'' && *end != '"')
                end++;
        }
        if (end > start)
        {
            word = ft_strndup(start, end - start);
            if (!word)
            {
                free_tokens(tokens);
                return NULL;
            }
            token = new_token(get_token_type(word), word);
            free(word);
            if (!token)
            {
                free_tokens(tokens);
                return NULL;
            }
            add_token(&tokens, token);
        }
        start = end;
    }
    return (tokens);
}
t_token     *new_token(int type, char *word)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if(!new)
        return (NULL);
    new->value = ft_strdup(word);
    if(!new->value)
        return (free(new), NULL); // test this line 
    new->type = type;
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
    if(line[0] == ';')
        return (TOKEN_SEMICOLON);
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
