/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:18:27 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/25 00:49:00 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_FUNCTIONS_H
# define BUILT_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/header.h"
#include "../includes/libft.h"
#include "../includes/header.h"
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

// char	**init_environment(char **system_envp);
char	**init_environment(t_head_list *head,char  **system_envp);
//void	free_environment(char **envp_ptr);
char	*my_getenv(const char *name, char **envp);
// char	*create_env_data(char *name, char *value);
char	*create_env_data(t_head_list *head,char *name, char *value);

int		find_var_index(const char *name_to_find, char **envp);
int		my_setenv(t_head_list *head ,char  *name, char *value, char ***env_ptr);
int		my_unsetenv(t_head_list *head, const char *name, char ***env_ptr);
int		ft_export(t_head_list *head,char **args, char ***env_ptr);
int		ft_pwd(char ***env_ptr);
int		ft_unset(t_head_list *head, char **args, char ***env_ptr); 

int		ft_env(char **args, char ***env_ptr);
// int		ft_exit(char **args, t_shell_data *data);
int ft_exit(t_head_list *head,char **args, char ***env_ptr, t_token *tokens, t_command *commands, int last_status);

int		ft_execute_command_list(t_head_list *head, t_command *command_list, char ***env_ptr);
char	*find_executable_path(t_head_list *head,char *cmd, char **envp);
int		wait_for_child(pid_t pid);
void	ft_free_array(char **array);
int		handle_command_not_found(char *cmd);
void	execute_child_process(char *cmd_path, char **args, char **envp);
int		ft_echo(char **args);
void	display_sorted_environment(t_head_list *head,char **envp);
int		process_export_arguments(t_head_list *head, char **args, char ***env_ptr);
int		is_standalone_name(const char *arg);
int		exec_export_name_only(t_head_list *head ,const char *name_arg, char ***env_ptr);
// int		exec_export_plus_equal(const char *arg, char ***env_ptr);
int		exec_export_value(t_head_list *head,const char *arg, char ***env_ptr);
// int		exec_export_name_only(const char *name_arg, char ***env_ptr);
void	print_err_export(const char *context, const char *specific_arg);
int		is_valid_identifier(const char *name);
int		handle_plus_equal_error(t_head_list *head,const char *plus_equal_ptr, char *name);
char	*strip_outer_quotes(t_head_list *head, const char *str);
int		create_append_value(t_head_list *head, char *name, char *append_val, char ***env_ptr);
int		is_built_ins(t_head_list *head,char **cmd, char ***env_ptr);
int		ft_chdir(t_head_list *head, char **args, char ***env_ptr);

#endif



