/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:18:27 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/14 16:46:55 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_FUNCTIONS_H
# define BUILT_FUNCTIONS_H

char	**init_environment(char **system_envp);
char	*my_getenv(const char *name, char **envp);
char	*create_env_data(char *name, char *value);
int		find_var_index(const char *name_to_find, char **envp);
int		my_setenv(char *name, char *value, char ***env_ptr);
int		my_unsetenv(const char *name, char ***env_ptr);
int		ft_export(char **args, char ***env_ptr);
void	display_sorted_environment(char **envp);


#endif



