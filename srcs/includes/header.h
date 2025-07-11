/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:06:01 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/11 04:01:42 by oait-si-         ###   ########.fr       */
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
#include <signal.h>

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
#define ERR_AMBIGUOS 9

#define T_WORD    0
#define T_PIPE    1
#define T_RED_IN  2 // <
#define T_RED_OUT 3 // >
#define T_APPEND  4 // >>
#define T_HEREDOC 5


typedef struct s_data
{
	int	delimiter;
	int	ex_status;
	int	quote_type;
	char *accumulator;
	int 	empty_expand;
	int is_expanded;
	int     is_assigning_expand;
	int 	has_whit_space;
}	t_data;

typedef struct s_token
{
	int				type;
	char			*value;
	int				quotes_type;
	int 			is_expanded_token;
	int 			is_empty_after_expand;
	int     is_assigning_expand_token;
	int 	has_whit_space;
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
int 	count_char(char *str);
char	*skip_space(char *str);
void	setup_signal_handlers(void);

int			handle_heredocs_before_execution(t_command *cmds, char **envp,
				t_data *data);
t_token		*process_token(t_token *token, t_command *cmd, t_indices *idx);
t_token		*handle_redirection(t_token *token, t_command *cmd,
				t_indices *idx);
int			ensure_command_exists(t_cmd_builder *builder, t_token *token);
char		*append_char(char *str, char c);
int			finalize_command(t_cmd_builder *builder);
void        handle_quoted_part(char **start, char **env, t_data *data);
void        handle_unquoted_part(char **start, char **env, t_data *data);
void		handle_question_mark(char **end, t_data *data);
int			is_space(char c);
int			is_operator(char c);
int			is_quotes(char c);
void        handle_regular_dollar(char **end, char **env, t_data *data);

char		*join_and_free(char *acc, char *to_add);
char		*handle_double_quote_var(char **end, char **env, char *accumulator);
char		*handle_double_quote_dollar(char **end, char *accumulator, char **env, t_data *data);
void        handle_double_quotes(char **start, char **env, t_data *data);
void        singel_quotes_handler(char **input_start, t_data *data);
void		free_double(char **arr);
void		free_args(t_command *command);
char		*question_mark(int ex_status);
int			get_quotes_type(char quote_type);
void        process_segment(char **start, char **env, t_data *data);
t_token		*handle_operator(char **start, t_data *data);
char		*handle_double_quote_var1(char **end, char **env, t_data *data,
				char *accumulator);
t_token		*handle_word(char **start, char **my_env, t_data *data);
void        handle_dollar_case(char **end, char **env, t_data *data);
void	terminate_arrays(t_command *cmd, t_indices *idx, t_counts counts);
void        handle_normal_char(char **end_ptr, t_data *data);
void        handle_regular_accumulator(char *var_start, char *end, char **env, t_data *data);
int	allocate_memory(t_command *cmd, t_counts counts);
void		error(int type);
int			validate_syntax(t_token *tokens, t_data *data);
t_token		*tokenize(char *line, char **my_env, t_data *data);
void		free_tokens(t_token *tokens);
int			populate_command(t_command *cmd, t_token *tokens, t_counts counts);
t_token    *new_token(int type, t_data *data);
void		add_token(t_token **tokens, t_token *token);
int			get_token_type(char *line, t_data *data);
char		*expand_value_func(char *value, char **envp);
t_command	*build_command(t_token *tokens);
void		add_command(t_command **commands, t_command *command);
char		*get_var_value(char *new_word, char **envp);
void		free_command(t_command *cmd);
t_command	*new_command(void);
void	    setup_child_signals(t_command *cmd);
int			should_skip_empty_command(t_cmd_builder *builder,t_token *first_word_token);
void		remove_empty_tokens(t_token **head);
void	perform_field_splitting(t_token **tokens);
int	get_operator_length(char **start, t_data *data);
void 	terminate_arr_finalize_command(t_cmd_builder *builder);
void	init_counts(t_counts *counts, t_cmd_builder *builder);
void	process_operator_data(char *operator_str, t_data *data);
void	reset_word_data(t_data *data);
void	sigint_handler(int sig);
int	handle_quotes(char *line);
int	check_double_quotes(char *line, int *i);
t_token	*create_tokens_from_split(char **split_words);
int	check_invalid_char(char *line);
int	is_redirection(int token_type);
void	remove_current_token(t_token **head, t_token **prev, t_token **current);
int	should_skip_empty_command(t_cmd_builder *builder, t_token *first_word_token);
static void	main_loop(char ***my_envp, t_data *data);
t_token	*create_and_add_token(t_token **tokens, t_token *token, t_data *data);
void	exit_status(int set, int value, t_data *data);
void	sigint_handler_exec(int sig);

#endif
