/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/07 23:33:13 by oait-si-         ###   ########.fr       */
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
    char 
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
// int     check_exit(char *line)
// {
//     int i;

//     i = 0;
//     while(line[i] && is_space(line[i]))
//         i++;
//     if(line[i] == '\0')
//         return 1;
//     if(ft_strncmp(line, "exit", 4) == 0)
//     {
//         i += 4;
//         while(line[i] && is_space(line[i]))
//             i++;
//         if(line[i] != '\0')
//         {
//             write(1,"Minishell: exit: ", 17);
//             while(line[i] && !is_space(line[i]))
//             {
//                 write(1, &line[i], 1);
//                 i++;
//             }
//             write(1, ": numeric argument required\n", 29);
//             return 1;
//         } 
//         return 0;
//     }
//     return 1;
// }
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