/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:06:01 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/12 02:31:38 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdbool.h>


#define TOKEN_WORD 0
#define TOKEN_PIPE 1
#define TOKEN_RED_IN 2 //<
#define TOKEN_RED_OUT 3//>
#define TOKEN_RED_APPEND 4 // >>
#define TOKEN_RED_HEREDOC 5 //<<
#define TOKEN_SEMICOLON 6

#define ERR_PIPE 1
#define ERR_RED 2
#define ERR_NEWLINE 5
#define ERR_QUOTE 6
#define ERR_SEMICOLON 7
#define ERR_SYNTAX 8 

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
void    error(int type);
int     validate_syntax(t_token *tokens);
t_token     *tokenize(char *line);
int ft_strlen(char *line);
char *ft_strdup(const char *s1);
int is_space(int  c);
size_t ft_strlcpy(char *dst, char *src, size_t dstsize);
char *ft_strndup( char *s, size_t n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void    free_tokens(t_token *tokens);
void    free_args(t_command *command);
t_token     *new_token(int type, char *word);
void    add_token(t_token **tokens, t_token *token);
int     get_token_type(char *line);
void    add_token(t_token **tokens, t_token *token);





#endif