/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:18:27 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/12 16:27:54 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_FUNCTIONS_H
# define BUILT_FUNCTIONS_H

char	**init_environment(char **system_envp);
char	*my_getenv(const char *name, char **envp);
char	*create_env_data(char *name, char *value);
int		find_var_index(char *str, char**envp);
int		my_setenv(char *name, char *value, char ***env_ptr);
int		my_unsetenv(const char *name, char ***env_ptr);
int		ft_echo(char **args);
int		ft_cd(char **args, char ***env_ptr);
int		ft_pwd(void);
int		ft_export(char **args, char ***env_ptr);
int		process_export_arguments(char **args, char ***env_ptr);
int		exec_export_plus_equal(const char *arg, char ***env_ptr);
char	*build_appended_value(const char *old_val, const char *val_to_append);
int		exec_export_value(const char *arg, char ***env_ptr);
void	print_err_111(const char *arg_part);
int		exec_export_name_only(const char *name_arg, char ***env_ptr);
void	display_sorted_environment(char **envp);
void	free_env_copy(char **env_copy);
int		count_env_vars(char **envp);

#endif