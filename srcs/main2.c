/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/07 23:15:31 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
// int ft_strlen(char *line)
// {
//     int i;

//     i = 0;
//     while(line[i])
//         i++;
//     return i;
// }

int is_space(int  c)
{
    return(c >= 9 && c <= 32);
}
// int check_line(char *line)
// {
//     int i;
    
//     i = 0;
//     while(line[i])
//     {
//         if(line[i] == '|')
//             return TOKEN_PIPE;
//         else if(line[i] == '>')
//     }
// }
// int     parse_line(t_token *token, char *line)
// {
//     int i;
//     int end;
//     int start;
//     char *line;
//     char token_value;
    
//     i = 0;
//     while(line[i])
//     {
//         while(is_space(line[i]))
//            i++;
//         start = i;
//         while(line[i] && !is_space(line[i]))
//             i++;
//         end = i ;
//         if(start < end)
//         {
//             line = ft_strdup(start, end, line);
//             if(!line)
//                 return 0;
//         }
//         token_value = check_line(line);
//         add_token(&token, token_value);
//     }
// }
void    t()
{
    system("leaks a.out");
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
int     check_exit(char *line)
{
    int i;

    i = 0;
    while(line[i] && is_space(line[i]))
        i++;
    if(line[i] == '\0')
        return 1;
    if(ft_strncmp(line, "exit", 4) == 0)
    {
        i += 4;
        while(line[i] && is_space(line[i]))
            i++;
        if(line[i] != '\0')
        {
            write(1,"Minishell: exit: ", 17);
            while(line[i] && !is_space(line[i]))
            {
                write(1, &line[i], 1);
                i++;
            }
            write(1, ": numeric argument required\n", 29);
            return 0;
        }
        else 
            return 0;
    }
    return 1;
}
int main()
{
    
    char *line;
    t_token *token;
      atexit(t);
   
    while(1)
    {
        line = readline("Minishell$ ");
        if(!line || !check_exit(line) )
        {
            write(1,"exit\n",5);
            exit(0);
        }
        if(*line)
            add_history(line);
        token = tokenize(line);
        free(line);
        
    }
    return 0;
}