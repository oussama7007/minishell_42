/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:06:01 by oait-si-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/05 18:31:51 by oait-si-         ###   ########.fr       */
=======
/*   Updated: 2025/05/05 14:40:18 by oadouz           ###   ########.fr       */
>>>>>>> 8d14088bb8cbcc455fb53adaab66dcdb5aa0e1b1
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




#define TOKEN_WORD 0
#define TOKEN_PIPE 1
#define TOKEN_RED_IN 2
#define TOKEN_RED_OUT 3
#define TOKEN_RED_APPEND 4
#define TOKEN_RED_HEREDOC 5
#define TOKEN_SEMICOLON 6



#define ERR_PIPE 1
#define ERR_RED 2
#define ERR_NEWLINE 5
#define ERR_QUOTE 6
#define ERR_SEMICOLON 7


typedef struct s_token {
    int type;              // Token type (e.g., TOKEN_WORD, TOKEN_PIPE)
    char *value;           // Token string (e.g., "ls", "|")
    struct s_token *next;  // Pointer to next token
} t_token;

typedef struct s_command {
    char *cmd;             // Command name (e.g., "ls")
    char **args;           // Array of arguments (e.g., {"ls", "-l"})
    char **red_in;         // Array of input redirection files
    char **red_out;        // Array of output redirection files
    int *append;           // Array of flags (1 for >>, 0 for >)
    char *heredoc_delimiter;// Delimiter for << (e.g., "EOF")
    struct s_command *next;// Next command (for pipes)
} t_command;

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
<<<<<<< HEAD
    char **args;
    char *output_file; //for <
    char *input_file; // for > or >> 
    struct s_command *next; // Pointer to the next command for pipes (struct s_command*).
}   t_command;
=======
    char                **args;
    char                *output_file;
    char                *input_file;
    struct s_command    *next;
}               t_command;
>>>>>>> 8d14088bb8cbcc455fb53adaab66dcdb5aa0e1b1





//tbon mok 