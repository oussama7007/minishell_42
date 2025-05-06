/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:18:27 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/06 18:21:58 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_FUNCTIONS_H
# define BUILT_FUNCTIONS_H

char	**init_environment(char **system_envp);
char	*my_getenv(const char *name, char **envp);
char	*create_env_data(char *name, char *value);
int		find_var_index(char *str, char**envp);
int		my_setenv(char *name, char *value, char ***env_ptr);

#endif