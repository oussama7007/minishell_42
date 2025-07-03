/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:06:01 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/03 14:41:06 by oadouz           ###   ########.fr       */
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

# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_RED_IN 2
# define TOKEN_RED_OUT 3
# define TOKEN_RED_APPEND 4
# define TOKEN_RED_HEREDOC 5

# define ERR_PIPE 1
# define ERR_RED 2
# define ERR_NEWLINE 5
# define ERR_QUOTE 6
# define ERR_SEMICOLON 7
# define ERR_SYNTAX 8

typedef struct s_data
{
	int	delimiter;
	int	ex_status;
	int	quote_type;
}	t_data;

typedef struct s_token
{
	int				type;
	char			*value;
	int				quotes_type;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	char				**red_in;
	char				**red_out;
	int					*append;
	char				**heredoc_delimiters;
	int					*heredoc_quotes;
	int					num_heredocs;
	char				*heredoc_tmp_file;
	struct s_command	*next;
}	t_command;

typedef struct s_indices
{
	int	i;
	int	j;
	int	k;
	int	append_idx;
	int	heredoc_idx;
}	t_indices;

typedef struct s_counts
{
	int	arg_c;
	int	in_c;
	int	out_c;
	int	heredoc_c;
}	t_counts;

typedef struct s_cmd_builder
{
	t_command	*commands;
	t_command	*current;
	t_token		*tokens_start;
	int			arg_count;
	int			red_in_count;
	int			red_out_count;
	int			heredoc_count;
}	t_cmd_builder;

// Function Prototypes
int			handle_heredocs_before_execution(t_command *cmds, char **envp,
				t_data *data);
t_token		*process_token(t_token *token, t_command *cmd, t_indices *idx);
t_token		*handle_redirection(t_token *token, t_command *cmd,
				t_indices *idx);
int			ensure_command_exists(t_cmd_builder *builder, t_token *token);
char		*append_char(char *str, char c);
int			finalize_command(t_cmd_builder *builder);
char		*handle_quoted_part(char **start, char **env, t_data *data);
char		*handle_unquoted_part(char **start, char **env, t_data *data);
char		*handle_question_mark(char **end, char *accumulator, t_data *data);
int			is_space(char c);
int			is_operator(char c);
int			is_quotes(char c);
char		*handle_regular_dollar(char **end, char **env, t_data *data,
				char *accumulator);
char		*join_and_free(char *acc, char *to_add);
char		*handle_double_quote_var(char **end, char **env, char *accumulator);
char		*handle_double_quote_dollar(char **end, char *accumulator,
				char **env, t_data *data);
char		*handle_double_quotes(char **start, char **env, t_data *data);
void		free_double(char **arr);
void		free_args(t_command *command);
char		*question_mark(int ex_status);
int			get_quotes_type(char quote_type);
char		*process_segment(char **start, char **env, t_data *data);
t_token		*handle_operator(char **start, t_data *data);
char		*handle_double_quote_var1(char **end, char **env, t_data *data,
				char *accumulator);
t_token		*handle_word(char **start, char **my_env, t_data *data);
char		*handle_dollar_case(char **end, char **env, char *accumulator,
				t_data *data);
char		*handle_normal_char(char **end_ptr, char *accumulator, t_data *data);
char		*handle_regular_accumulator(char *var_start, char *end, char **env,
				char *accumulator);
void		error(int type);
int			validate_syntax(t_token *tokens);
t_token		*tokenize(char *line, char **my_env, t_data *data);
void		free_tokens(t_token *tokens);
int			populate_command(t_command *cmd, t_token *tokens, t_counts counts);
t_token		*new_token(int type, char *word, int quotes_type);
void		add_token(t_token **tokens, t_token *token);
int			get_token_type(char *line);
void		add_token(t_token **tokens, t_token *token);
char		*expand_value_func(char *value, char **envp);
t_command	*build_command(t_token *tokens);
void		add_command(t_command **commands, t_command *command);
char		*get_var_value(char *new_word, char **envp);
void		free_command(t_command *cmd);
t_command	*new_command(void);
void		setup_signals(void);
void		setup_child_signals(void);

#endif
