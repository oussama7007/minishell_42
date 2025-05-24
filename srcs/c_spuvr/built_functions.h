/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:18:27 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/24 18:26:55 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_FUNCTIONS_H
# define BUILT_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/header.h"
#include "../c_spuvr/LIBFT/libft.h"
#include "../includes/header.h"
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

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
// int		ft_exit(char **args, t_shell_data *data);
int		ft_execute_command_list(t_command *command_list, char ***env_ptr);
char	*find_executable_path(char *cmd, char **envp);
int		wait_for_child(pid_t pid);
int		is_direct_path(const char *cmd_name);

//cd 
void	up_env_cd(char *old_pwd_val, const char *path_arg, char ***env_ptr);
char	*target_path(char **args, char **envp, int *frree);


// erro.c
void	ft_free_array(char **array);
int		handle_command_not_found(char *cmd);
void	execute_child_process(char *cmd_path, char **args, char **envp);
int		ft_print_exec_error(char *cmd_name, int err_no);
int		handle_fork_error(char *cmd_to_free);

int		ft_echo(char **args);
void	display_sorted_environment(char **envp);
int		process_export_arguments(char **args, char ***env_ptr);
int		is_standalone_name(const char *arg);
int		exec_export_name_only(const char *name_arg, char ***env_ptr);
int		exec_export_plus_equal(const char *arg, char ***env_ptr);
int		exec_export_value(const char *arg, char ***env_ptr);
int		exec_export_name_only(const char *name_arg, char ***env_ptr);
void	print_err_export(const char *context, const char *specific_arg);
int		is_valid_identifier(const char *name);
int		handle_plus_equal_error(const char *plus_equal_ptr, char *name);
char	*strip_outer_quotes(const char *str);
int		create_append_value(char *name, char *append_val, char ***env_ptr);
int		is_built_ins(char **cmd, char ***env_ptr);
int		ft_chdir(char **args, char ***env_ptr);

#endif



