/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:18:20 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/07 09:51:12 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H
# include <unistd.h>
# include <stdlib.h>
# include "built_functions.h"
# include "LIBFT/libft.h"

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

#endif