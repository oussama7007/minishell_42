/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/09 23:15:15 by oait-si-         ###   ########.fr       */
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
int ft_strlen(char *line)
{
    int i;

    i = 0;
    while(line[i])
        i++;
    return i;
}

int is_space(int  c)
{
    return(c >= 9 && c <= 32);
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
        while(tmp)
            tmp = tmp->next;
        tmp->next = token;
    }
} 
t_token     *new_token(int type, char *word)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if(!new)
        return (NULL);
    new->value = ft_strdup(word);
    if(!new->value)
        return (NULL);
    new->type = type;
    new->next = NULL;
    return new;
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

t_token     *tokenize(char *line)
{
    t_token *tokens = NULL;
    char *start;
    char *end;
    char *word;
    t_token *token;
    
    start = line;
    while(*start)
    {
        while(*start == ' ')
            start++;
        if(!*start)
            break;
        end = start;
        if(*start == '|' || *start == ';' || *start == '<' || *start == '>')
        {
            if(*start == '<' && *(start + 1) == '<')
                end +=2;
            if(*start == '>' && *(start + 1) == '>')
                end +=2;
            else 
                end++;
        }
        else 
            while(*end && *end != '|' && *end != ';' && *end != '<' && *end != ' ' && *end != '>')
                end++;
        if(end > start)
        {
            word = ft_strndup(line, end - start);
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
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n) && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
void    print_tokens(t_token *tokens)
{
    while(tokens)
    {
        printf(" type : %d, value %s \n", tokens->type, tokens->value);
        tokens = tokens->next;
    }
    
}
void    t()
{
    system("leaks a.out");
}
int main()
{
    
    char *line;
    t_token *tokens;
    atexit(t);
   
    while(1)
    {
        line = readline("Minishell$ ");
        if(!line )
        {
            write(1,"exit\n",5);
            exit(0);
        }
        if(*line)
            add_history(line);
        tokens = tokenize(line);
        if(!tokens)
        {
            free(line);
            continue;
        }
       print_tokens(tokens); // for dubg
        free_tokens(tokens);
        free(line);
        
    }
     exit(0);
}