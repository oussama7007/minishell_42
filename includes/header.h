/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:06:01 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/05 14:39:01 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdbool.h>





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

#define command 0
#define pipe 0
typedef struct s_command
{
    char                **args;
    char                *output_file;
    char                *input_file;
    struct s_command    *next;
}               t_command;

