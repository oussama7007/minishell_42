/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/06 21:35:48 by oait-si-         ###   ########.fr       */
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
int check_line(char *line)
{
    int i;
    
    i = 0;
    while(line[i])
    {
        if(line[i] == '|')
            return TOKEN_PIPE;
        else if(line[i] == '>')
    }
}
int     parse_line(t_token *token, char *line)
{
    int i;
    int end;
    int start;
    char *line;
    char token_value;
    
    i = 0;
    while(line[i])
    {
        while(is_space(line[i]))
           i++;
        start = i;
        while(line[i] && !is_space(line[i]))
            i++;
        end = i ;
        if(start < end)
        {
            line = ft_strdup(start, end, line);
            if(!line)
                return 0;
        }
        token_value = check_line(line);
        add_token(&token, token_value);
    }
}
int main()
{
    char *line;
    t_token *token;
    
   
    while(1)
    {
        line = readline("Minishell$ ");
        if(!line)
        {
            write(1,"exit\n",5);
            exit(0);
        }
        if(!parse_line(token, line))
            return(0);
        free(line);
        
    }

}