/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:18:27 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/12 18:16:24 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_FUNCTIONS_H
# define BUILT_FUNCTIONS_H

# include <stdio.h>    
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../includes/header.h"
# include "../c_spuvr/LIBFT/libft.h"
# include "../includes/header.h"
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_heredoc_info
{
	int			fd;
	int			i;
	t_command	*cmd;
	char		**envp;
	t_data		*data;
}				t_heredoc_info;

typedef struct s_exit_data
{
	char		***env_ptr;
	t_command	*commands;
	t_token		*tokens;
	t_data		*data;
}				t_exit_data;

int		is_nn_option(const char *arg);
// heredoc
void	expand_heredoc_line(char *line, char **env, t_data *data);
char	*generate_heredoc_filename(void);
void	handle_heredoc_interrupt(t_heredoc_info *info, int fd_backup);
int		process_heredoc_iteration(t_heredoc_info *info, const char *filename);
int		should_stop_reading(char *line, t_heredoc_info *info);
void	read_heredoc_loop(t_heredoc_info *info);
//built is
char	**init_environment(char **system_envp);
void	free_environment(char **envp_ptr);
char	*my_getenv(const char *name, char **envp);
char	*create_env_data(char *name, char *value);
int		find_var_index(const char *name_to_find, char **envp);
int		my_setenv(char *name, char *value, char ***env_ptr);
int		my_unsetenv(const char *name, char ***env_ptr);
int		ft_export(char **args, char ***env_ptr);
int		ft_pwd(char ***env_ptr);
int		ft_unset(char **args, char ***env_ptr);
int		ft_env(char **args, char ***env_ptr);
int		ft_execute_command_list(t_command *command_list, t_token *tokens,
			char ***env_ptr, t_data *data);
char	*find_executable_path(char *cmd, char **envp);
int		wait_for_child(pid_t pid);
int		is_direct_path(const char *cmd_name);
// execute
void	read_heredoc_input(t_heredoc_info *info);
int		should_stop_reading(char *line, t_heredoc_info *info);
void	re_process_heredoc_line(t_heredoc_info *info, char *line);
void	handle_heredoc_interrupt(t_heredoc_info *info, int fd_backup);
char	*setup_heredoc_to_file(t_command *cmd, char **envp, t_data *data);
void	heredoc_signals(int sig);
int		is_parent_only_builtin(char *cmd);
int		has_redirection(t_command *cmd);
int		setup_heredoc(t_command *cmd, char **envp, t_data *data);
void	try_paths(char **paths, char *cmd, char **cmd_path);
//exit
int		ft_exit(char **args, t_exit_data *exit_data);
int		is_numeric_arg(char *str);
int		ft_exit_child(char **args);

//cd 
void	up_env_cd(char *old_pwd_val, const char *path_arg, char ***env_ptr);
char	*target_path(char **args, char **envp);
// redirection
int		handle_redirection_child(t_command *cmd_node);
// pipe
int		execute_pipeline(t_command *commands, char ***env_ptr, t_data *data);
void	execute_single_cmd(t_command *cmd, char **envp);
void	setup_child_io(int prev_pipe, int *pipe_fds, t_command *cmd);
void	child_process_logic(t_command *cmd, char ***env);

// erro.c
void	ft_free_array(char **array);
int		handle_command_not_found(char *cmd);
void	execute_child_process(char *cmd_path, char **args, char **envp);
int		handle_fork_error(char *cmd_to_free);
int		ft_echo(char **args);
void	display_sorted_environment(char **envp);
int		process_export_arguments(char **args, char ***env_ptr);
int		exec_export_value(const char *arg, char ***env_ptr);
int		exec_export_name_only(const char *name_arg, char ***env_ptr);
void	print_err_export(const char *context, const char *specific_arg);
int		is_valid_identifier(const char *name);
char	*strip_outer_quotes(const char *str);
int		create_append_value(char *name, char *append_val, char ***env_ptr);
int		is_built_ins(char **cmd, char ***env_ptr);
int		ft_chdir(char **args, char ***env_ptr);
void	ensure_minimal_env(char ***env_ptr);

void	set_to_null(t_command	**commands,t_token **tokens, char **line );
void	clean_two_strings(char *str1, char *str2);

#endif