/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:06:01 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/17 12:19:07 by oait-si-         ###   ########.fr       */
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
    int quotes_type;      // 0 for non quotes , 1 for single quotes, 2 for double quotes
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
void    free_gc(t_head_list *head);
/// ls -al <input1 <intpu2 arg1 arg2 arg3 >output1 | grep 

//expand
t_token *expand(t_token **tokens,char **env);
void        error(int type);
int         validate_syntax(t_token *tokens);
t_token     *tokenize(char *line, char **my_env, int ex_status);
int         is_space(int  c);
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


// #include <stdlib.h>
// #include <string.h>
// typedef struct s_gc_list {
//     void *ptr;
//     struct s_gc_list *next;
// } t_gc_list;

// typedef struct s_head_list {
//     t_gc_list *head;
// } t_head_list;

// void gc_init(t_head_list *head);
// void *gc_malloc(t_head_list *head, size_t size);
// void gc_free_all(t_head_list *head);
// char *gc_strdup(t_head_list *head, const char *s);

// void gc_init(t_head_list *head) {
//     if (head) head->head = NULL;
// }
// void gc_free_all(t_head_list *head) {
//     if (!head) return;
//     t_gc_list *curr = head->head;
//     while (curr) {
//         t_gc_list *next = curr->next;
//         free(curr->ptr);
//         free(curr);
//         curr = next;
//     }
//     head->head = NULL;
// }

// char *gc_strdup(t_head_list *head, const char *s) {
//     if (!s) return NULL;
//     size_t len = strlen(s) + 1;
//     char *dup = gc_malloc(head, len);
//     if (!dup) return NULL;
//     ft_memcpy(dup, s, len);
//     return dup;
// }




// void *gc_malloc(t_head_list *head, size_t size) {
//     if (!head) return NULL;

//     void *ptr = malloc(size);
//     if (!ptr) {
//         gc_free_all(head);
//         write(2, "gc_malloc: failed to allocate for a ptr\n",ft_strlen("gc_malloc: failed to allocate for a ptr\n"));
//         exit(EXIT_FAILURE);// 1
//     }

//     t_gc_list *node = malloc(sizeof(t_gc_list));
//     if (!node) {
//         free(ptr);
//         gc_free_all(head);
//         write(2,"gc_malloc: failed to allocate node\n",ft_strlen("gc_malloc: failed to allocate node\n"));
//         exit(EXIT_FAILURE);// 1
//     }

//     node->ptr = ptr;
//     node->next = head->head;
//     head->head = node;
//     return ptr;
// }
// #ifndef HEADER_H
// #define HEADER_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include "libft.h"
// #include <sys/wait.h>
// #include <unistd.h>
// #include <stdbool.h>


// #define TOKEN_WORD 0
// #define TOKEN_PIPE 1
// #define TOKEN_RED_IN 2 //<
// #define TOKEN_RED_OUT 3//>
// #define TOKEN_RED_APPEND 4 // >>
// #define TOKEN_RED_HEREDOC 5 //<<


// #define ERR_PIPE 1
// #define ERR_RED 2
// #define ERR_NEWLINE 5
// #define ERR_QUOTE 6
// #define ERR_SEMICOLON 7
// #define ERR_SYNTAX 8 

// typedef struct s_token {
//     int type;              // Token type (e.g., TOKEN_WORD, TOKEN_PIPE)
//     char *value;           // Token string (e.g., "ls", "|")
//     struct s_token *next;  // Pointer to next token
// } t_token;

// typedef struct s_command {
//     char *cmd;             // Command name (e.g., "ls")
//     char **args;           // Array of arguments (e.g., {"ls", "-l"})
//     char **red_in;         // Array of input redirection files
//     char **red_out;        // Array of output redirection files
//     int *append;           // Array of flags (1 for >>, 0 for >)
//     char *heredoc_delimiter;// Delimiter for << (e.g., "EOF")
//     struct s_command *next;// Next command (for pipes)
// } t_command;



// /// ls -al <input1 <intpu2 arg1 arg2 arg3 >output1 | grep

// void        error(int type);
// int         validate_syntax(t_token *tokens);
// //t_token     *tokenize(char *line);
// t_token     *tokenize(t_head_list *head, char *line);
// int         is_space(int  c);
// void        free_tokens(t_token *tokens);
// void        free_args(t_command *command);
// // t_token     *new_token(int type, char *word);
// t_token     *new_token(t_head_list *head,int type, char *word);
// void        add_token(t_token **tokens, t_token *token);
// int         get_token_type(char *line);
// void        add_token(t_token **tokens, t_token *token);

// t_command *build_command(t_head_list *head, t_token *tokens);
// void add_command(t_command **commands, t_command *command);
// //static int populate_command(t_command *cmd, t_token *tokens, int arg_c, int in_c, int out_c);
// //void free_command(t_command *cmd);
// t_command *new_command(t_head_list *head);


// #endif