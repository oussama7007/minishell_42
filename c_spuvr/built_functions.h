/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:18:27 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/15 17:54:24 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_FUNCTIONS_H
# define BUILT_FUNCTIONS_H

char	**init_environment(char **system_envp);
void	free_environment(char **envp_ptr);
char	*my_getenv(const char *name, char **envp);
char	*create_env_data(char *name, char *value);
int		find_var_index(const char *name_to_find, char **envp);
int		my_setenv(char *name, char *value, char ***env_ptr);
int		my_unsetenv(const char *name, char ***env_ptr);
int		ft_export(char **args, char ***env_ptr);
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


#endif



