

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/06 18:05:18 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"


char *ft_strdup(const char *s1)
{
    int i = 0;
    char *copy;

    while (s1[i])
        i++;

    copy = (char *)malloc(sizeof(char) * (i + 1));
    if (!copy)
        return NULL;

    i = 0;
    while (s1[i])
    {
        copy[i] = s1[i];
        i++;
    }
    copy[i] = '\0';

    return copy;
}
int ft_strlen(char *line)
{
    int i;

    i = 0;
    while(line[i])
        i++;
    return i;
}
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i = 0;

    
    while (src[i])
        i++;

    if (dstsize == 0)
        return i;

    size_t j = 0;
    while (j < dstsize - 1 && src[j])
    {
        dst[j] = src[j];
        j++;
    }

    dst[j] = '\0'; 

    return i; 
}
char *ft_strndup( char *s, size_t n)
{
    char *dup;
    size_t len;

    len = ft_strlen(s);
    if (len > n)
        len = n;
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    ft_strlcpy(dup, s, len + 1);
    return (dup);
}
void    free_tokens(t_token *tokens);
// Helper: Create a new token
static t_token *new_token(int type, char *value)
{

    t_token *token;
    
    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = ft_strdup(value);
    if (!token->value)
    {
        free(token);
        return (NULL);
    }
    token->next = NULL;

    return (token);
}

// Helper: Add token to list
static void add_token(t_token **list, t_token *new)
{
    t_token *tmp;

    if (!*list)
        *list = new;
    else
    {
        tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

// Helper: Check token type for substring
static int get_token_type(char *str)
{
    if (str[0] == '|')
        return (TOKEN_PIPE);
    if (str[0] == '>' && str[1] == '>' )
        return (TOKEN_RED_APPEND);
    if (str[0] == '>' )
        return (TOKEN_RED_OUT);
    if (str[0] == '<' && str[1] == '<')
        return (TOKEN_RED_HEREDOC);
    if (str[0] == '<')
        return (TOKEN_RED_IN);
    if (str[0] == ';')
        return (TOKEN_SEMICOLON);
    return (TOKEN_WORD);
}

// Tokenize input string
t_token *tokenize(char *line)
{
    t_token *tokens = NULL;
    char *start = line;
    char *end;

    while (*start)
    {
        while (*start == ' ')
            start++;
        if (!*start)
            break;
        end = start;
        if (*start == '|' || *start == ';' || *start == '<' || *start == '>')
        {
            if (*start == '>' && *(start + 1) == '>')
                end += 2;
            else if (*start == '<' && *(start + 1) == '<')
                end += 2;
            else
                end++;
        }
        else
            while (*end && *end != ' ' && *end != '|' && *end != ';' && *end != '<' && *end != '>')
                end++;
        if (end > start)
        {
            char *word = ft_strndup(start, end - start);
            if (!word)
                return (free_tokens(tokens), NULL);
            t_token *token = new_token(get_token_type(word), word);
            free(word);
            if (!token)
                return (free_tokens(tokens), NULL);
            add_token(&tokens, token);
        }
        start = end;
    }
    return (tokens);
}

// Free token list
void    free_tokens(t_token *tokens)
{
    t_token *tmp ;
    while(tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);       
    }
}
// Debug: Print tokens
static void print_tokens(t_token *tokens)
{
    while (tokens)
    {
        printf("Token: type=%d, value=%s\n", tokens->type, tokens->value);
        tokens = tokens->next;
    }
}
void    t()
{
    system("leaks a.out");
}
int main(void)
{
    char *line;
    t_token *tokens;
    atexit(t);
    while (1)
    {
        line = readline("Minishell$ ");
        if (!line)
        {
            write(1, "exit\n", 5);
            exit(0);
        }
        if (*line)
            add_history(line);
        tokens = tokenize(line);
        if (!tokens)
        {
            free(line);
            continue;
        }
        print_tokens(tokens); // for dubg
        free_tokens(tokens);
        free(line);
    }
    
    return (0);
}