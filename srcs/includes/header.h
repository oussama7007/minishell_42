/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:06:01 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/23 01:50:10 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../c_spuvr/LIBFT/libft.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>


#define TOKEN_WORD 0
#define TOKEN_PIPE 1
#define TOKEN_RED_IN 2 //<
#define TOKEN_RED_OUT 3//>
#define TOKEN_RED_APPEND 4 // >>
#define TOKEN_RED_HEREDOC 5 //<<


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

typedef struct s_gc_list
{
    void *ptr;
    struct s_gc_list *next;
}t_gc_list;

typedef struct s_head_list
{
    t_gc_list *head;
} t_head_list;
// garbage collecter 
void    add_ptr_node(t_head_list **head, void *ptr);
void *gc_malloc(t_head_list **head,int size);
/// ls -al <input1 <intpu2 arg1 arg2 arg3 >output1 | grep 
void        error(int type);
int         validate_syntax(t_token *tokens);
t_token     *tokenize(char *line);
int         is_space(int  c);
void        free_tokens(t_token *tokens);
void        free_args(t_command *command);
t_token     *new_token(int type, char *word);
void        add_token(t_token **tokens, t_token *token);
int         get_token_type(char *line);
void        add_token(t_token **tokens, t_token *token);

t_command *build_command(t_token *tokens);
void add_command(t_command **commands, t_command *command);
//static int populate_command(t_command *cmd, t_token *tokens, int arg_c, int in_c, int out_c);
void free_command(t_command *cmd);
t_command *new_command(void);


#endif