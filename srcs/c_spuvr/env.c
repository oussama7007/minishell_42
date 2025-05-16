/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:00:09 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/16 14:14:00 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

char	*my_getenv(const char *name, char **envp)
{
	int		i;
	int		n_len;

	if (!name || !envp)
		return (NULL);
	1 && (i = 0, n_len = 0);
	while (name[n_len])
		n_len++;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, n_len) == 0 && envp[i][n_len] == '=')
			return (&envp[i][n_len + 1]);
		i++;
	}
	return (NULL);
}

int	my_setenv(char *name, char *value, char ***env_ptr)
{
	int		var;
	char	*new_value;
	char	**new_data;

	if (!name || !env_ptr)
		return (-1);
	var = find_var_index(name, *env_ptr);
	new_value = create_env_data(name, value);
	if (!new_value)
		return (-1);
	if (var != -1)
	{
		free((*env_ptr)[var]);
		(*env_ptr)[var] = new_value;
		return (0);
	}
	var = ft_arrlen(*env_ptr);
	if (!(new_data = malloc((var + 2) * sizeof(char *))))
		return (free(new_value), -1);
	ft_memcpy(new_data, *env_ptr, var * sizeof(char *));
	new_data[var] = new_value;
	new_data[var + 1] = NULL;
	free(*env_ptr);
	*env_ptr = new_data;
	return (0);
}

static void	copy_indexes(char ***env_ptr, char **new_env, int skip_idx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*env_ptr)[i])
	{
		if (i != skip_idx)
			new_env[j++] = (*env_ptr)[i];
		else
			free((*env_ptr)[i]);
		i++;
	}
	new_env[j] = NULL;
}

int	my_unsetenv(const char *name, char ***env_ptr)
{
	int		var_id;
	char	**new_env;
	int		env_size;

	if (!name || !env_ptr || !(*env_ptr))
		return (-1);
	var_id = find_var_index((char *)name, *env_ptr);
	if (var_id == -1)
		return (0);
	env_size = ft_arrlen(*env_ptr);
	new_env = malloc(sizeof(char *) * env_size);
	if (!new_env)
		return (-1);
	copy_indexes(env_ptr, new_env, var_id);
	free(*env_ptr);
	*env_ptr = new_env;
	return (0);
}
