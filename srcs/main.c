/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 00:37:18 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/04 18:26:15 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void ft_error(int type);
typedef struct s_parscmd 
{
        char *line;
}   t_parscmd;

int ft_strlen(char *line)
{
    int i;

    i = 0;
    while(line[i])
        i++;
    return i;
}
int is_char(int c )
{
        return (c > 32 && c <= 127 && c != '|' && c != '&' && c != '<' && c != '>' && c != ')' );
}
int     valid_pipe(char *line)
{
    int i;
    int pipe_flag;
    int len;

    len = ft_strlen(line);
    pipe_flag = 0;

    i = -1;
    while(line[++i])
    {
        if(line[i] == '|'  && line[i + 1] == '|' && !pipe_flag)
             return (ft_error(2),0);
        if(is_char(line[i]))
            pipe_flag = 1;
        if(line[i] == '|' && !pipe_flag)
            return (ft_error(1),0);
    }
    return 1;
}
int     and_operator(char *line)     
{
        int i;
        int and_flag;

        i = -1;
        and_flag = 0;
        while(line[++i])
        {
                if(is_char(line[i]))
                    and_flag = 1;
                if(line[i] == '&' && !and_flag)
                {
                    if(line[i + 1] == '&')
                        return(ft_error(4), 0);
                    return (ft_error(3), 0);
                }
        }
        return 1;
}
int     new_line(char *line)
{
    int i;
    int first_flag;
    int second_flag;
    int len;
    
    first_flag = 0;
    second_flag = 0;
    len = ft_strlen(line);
    i = -1;
    while(len >= 0 && (line[len] != '<' ||  line[len] != '>')) // need to fix 
    {
        if(is_char(line[len]))
            second_flag = 1; 
        len--;
    }
   // if(!second_flag) // need to fix 
      //   return(ft_error(4), 0);
    while(line[++i])
    {

        if(is_char(line[i]))
            first_flag = 0;
        if((line[i] == '<' || line[i] == '>') && !first_flag)
            return(ft_error(4), 0);
    }
    return 1;
}
// need update 
int     parentheses(char *line)
{
    int i;
    int first_flag;
    int second_flag;
    int len;

    second_flag = 0; 
    len = ft_strlen(line);

    first_flag = 0;
    i = -1;
    while(len-- >= 0)
    {
        if(is_char(line[len]))
            first_flag = 1;
    }
   // if(first_flag)
      //  return (ft_error(6),0);
    // while(line[++i])
    // {
    //     if(is_char(line[i]))
    //         second_flag = 1;
        
    // }
    return 1;

}
int     check_line(char *line)
{   
    if(!and_operator(line))
        return (0);
    else if(!valid_pipe(line))
        return(0);
    else if(!new_line(line))
        return(0);
    else if(!parentheses(line))
        return(0);
    else 
        return 1;
}
void ft_putstr_fd(char *line, int fd)
{
    int i;

    i = -1;
    while(line[++i])
        write(2, &line[i], 1);
}
void ft_error(int type)
{
    if(type == 1)
        ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
    else if(type == 2)
        ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
    else if(type == 3)
        ft_putstr_fd("bash: syntax error near unexpected token `&'\n", 2);
    else if(type == 4)
        ft_putstr_fd("bash: syntax error near unexpected token `&&'\n", 2);
    else if(type == 5)
        ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
    else if(type == 6)
        ft_putstr_fd("bash: syntax error near unexpected token `)'\n", 2);
    else 
        ft_putstr_fd("bash: syntax error \n", 2);
}
int main(void)  
{
    t_parscmd arguse;
    t_parscmd *arg = &arguse; 
    while(1)
    { 
        (*arg).line = readline("minishell$ ");
    
        if(!check_line((*arg).line))
            // return(free((*arg).line), 1);
        free(arg->line);
    }
}

/// ls -al <input1 <intpu2 arg1 arg2 arg3 >output1 | grep 

/*
    #define COMMAND 0
    #define PIPE    1
    
    node{
        char **args;
        char **red_in;
        char **red_out;
        int type;
        node *next;
    }

*/