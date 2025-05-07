/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:00:09 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/07 09:46:26 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h"
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

char	*create_env_data(char *name, char *value)
{
	int		n_len;
	int		v_len;
	char	*entry;

	n_len = ft_strlen(name);
	v_len = ft_strlen(value);
	entry = malloc(n_len + v_len + 2);	// Allocate memory for "name=value\0" string  || // +1 for '=', +1 for '\0'
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, name, n_len + 1);
	entry[n_len] = '=';
	ft_strlcpy(entry + n_len + 1, value, v_len + 1);	
	return (entry);
}

int	find_var_index(char *str, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	my_setenv(char *name, char *value, char ***env_ptr)
{
	int		var;
	char	*new_value;
	char	**new_data;

	if (!name || !value || !env_ptr)
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
