/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/06 17:16:48 by oait-si-         ###   ########.fr       */
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
    return(c >= 9 &&  c <= 32);
}
int     parse_line(t_token *token, char *line)
{
    int i;
    int end;
    int start;
    i = 0;
    while(line[i])
    {
        while(is_space(line[i]))
           i++;
        start = i;
        while(line[i] && !is_space(line[i]))
            i++;
        end = i ;
         
    }
}
int main()
{
    t_token *token;
    
    char *line;
    while(1)
    {
        line = readline("Minishell$ ");
        if(!parse_line(token, line))
            return(0);
        free(line);
        
    }

}