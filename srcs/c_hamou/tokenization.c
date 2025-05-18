<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:12:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/17 15:16:50 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

=======
>>>>>>> ff410c67dbdea7e2c3110b278df675aa6bd523d2
#include "header.h"
// t_token     *tokenize(char *line)
// {
//     t_token *tokens;
//     char *start;
//     char *end;
//     char *word;
//     t_token *token;
    
//     tokens = NULL;
//     start = line;
//     while(*start)
//     {
//         while(*start == ' ')
//             start++;
//         if(!*start)
//             break;
//         end = start;
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
//  need to handles quotes 
t_token     *tokenize(char *line)
{
    t_token *token;
    char    *start;
    char    *end;
    char *word;
    t_token *tokens;
    
    start = line;
    while(*start)
    {
        while(*start == ' ' && *start != '\'' && *start != '"')
            start++;
        if(!*start)
            break;
        end = start;
        if(*start == '\'' || *start == '"')
        {
            if(*start == '"')
            {
                end++;
                printf("if *start == \" \n");
                while( *end && *end != '"')
                    end++;
            }
            else 
            {
                printf("else\" \n");
                end++;
                while(*end && *end != '\'')
                    end++;
            }
            printf("end : '%s' ---- start '%s'\n" , end, start);
            if(end > start)
            {
                printf("ente the condition of end > start");
                word = ft_strndup(start, end - start);
            
                if(!word)
                    return(free_tokens(tokens), NULL);
                token = new_token(get_token_type(word),word);
                printf("after tokne\n");
                if(!token)
                    return(free_tokens(tokens), NULL);
                free(word);
                add_token(&tokens, token);
                printf("after add tokne\n");
                start = end;
            }
        }
        if(*start == '|' || *start == ';' || *start == '<' || *start == '>')
        {
            if(*start == '<' && *(start + 1) == '<')
                end +=2;
            else if(*start == '>' && *(start + 1) == '>')
                end +=2;
            else
                end++;
        }
        else
            while(*end && *end != '|' && *end != ';' && *end != '<' && *end != ' ' && *end != '>')
                end++;
        if(end > start)
        {
            word = ft_strndup(start, end - start);
            if(!word)
                return(free_tokens(tokens),NULL);
            token = new_token(get_token_type(word), word);
            free(word);
            if(!token)  
                return(free_tokens(tokens), NULL);
            add_token(&tokens, token);
        }
        start = end;
    }
    return(tokens);
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
    t_token *tmp;
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
