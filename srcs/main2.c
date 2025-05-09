/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/09 15:06:17 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
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
t_token     *tokenize(char *line)
{
    t_token *tokens = NULL;
    char *start;
    char *end;
    char *word;
    t_token *token;
    
    start = &line;
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
            while(*start && *start != '|' || *start != ';' || *start != '<' || *start != '>')
                end++;
        if(end > start)
        {
            word = ft_strndup(start, end ,line);
            if(!word)
                return(NULL);
            token = new_token(get_token_type(word), word);
            free(word);
            if(!token)  
                retrun(free_token(tokens))
            add_token(&token, NULL);
                    
        }
    }
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
void    t()
{
    system("leaks a.out");
}
int main()
{
    
    char *line;
    t_token *token;
    atexit(t);
   
    while(1)
    {
        line = readline("Minishell$ ");
        if(!line )
        {
            write(1,"exit\n",5);
            free(line);
            exit(0);
        }
        if(*line)
            add_history(line);
        token = tokenize(line);
        free(line);
        
    }
    return 0;
}