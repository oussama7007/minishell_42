/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:06:01 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/01 23:10:13 by oadouz           ###   ########.fr       */
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


typedef struct s_heredoc {
    char                *delimiter;
    int                 quotes;
    char                *tmp_file; // To store the temporary file name
    struct s_heredoc    *next;
} t_heredoc;


typedef struct s_data
{
    int delimiter;
    int ex_status;
    int quote_type;
}t_data;

typedef struct s_token {
    int type;              // Token type (e.g., TOKEN_WORD, TOKEN_PIPE)
    char *value;           // Token string (e.g., "ls", "|")
    int quotes_type;       // 0 for non quotes , 1 for single quotes, 2 for double quotes
                           // 0 for 
    struct s_token *next;  // Pointer to next token
} t_token;

typedef struct s_command {
    char                *cmd;
    char                **args;
    char                **red_in;
    char                **red_out;
    int                 *append;
    t_heredoc           *heredocs;
    struct s_command    *next;
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


char *handle_quoted_part(char **start, char **env, t_data *data);
char *handle_unquoted_part(char **start, char **env,t_data *data);

int     is_space(char c);
int     is_operator(char c);
int     is_quotes(char c);

// tokens utils
char *qestion_mark(int ex_status);
int get_quotes_type(char quote_type);
char *process_segment(char **start, char **env, t_data *data);
t_token *handle_operator(char **start, t_data *data);
//expand
t_token *handle_word(char **start,char **my_env, t_data *data );
char *handle_dollar_case(char **end, char **env, char *accumulator, t_data *data);
char *handle_normal_char(char **end_ptr, char *accumulator, t_data *data);
char *Handle_regular_accumualtor(char *var_start, char *end, char **env, char *accumulator);
void        error(int type);
int         validate_syntax(t_token *tokens);
t_token     *tokenize(char *line, char **my_env, t_data *data);
// int         is_space(int  c);
void        free_tokens(t_token *tokens);
void        free_args(t_command *command);
t_token     *new_token(int type, char *word, int quotes_type);
void        add_token(t_token **tokens, t_token *token);
int         get_token_type(char *line);
void        add_token(t_token **tokens, t_token *token);
 char *expand_value_func(char *value, char **envp);
t_command *build_command(t_token *tokens);
void add_command(t_command **commands, t_command *command);
char *get_var_value(char *new_word, char **envp);
//static int populate_command(t_command *cmd, t_token *tokens, int arg_c, int in_c, int out_c);
void free_command(t_command *cmd);
t_command *new_command(void);

//signals
void	setup_signals(void);
void	setup_child_signals(void);

#endif