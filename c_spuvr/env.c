/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:00:09 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/06 17:32:00 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h"

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

static char	create_env_data(char *name, char *value)
{
	int		i;
	int		j;
	int		n_len;
	int		v_len;
	char	*entry;

	1 && (i = 0, j = 0, n_len = ft_strlen(name), v_len = ft_strlen(value));
	entry = malloc(n_len + v_len + 2);	// Allocate memory for "name=value\0" string  || // +1 for '=', +1 for '\0'
	if (!entry)
		return (NULL);
	while (i++ < n_len)
		entry[i] = name[i];
	entry[i] = '=';
	while (j++ < v_len)
		entry[i + j] = value[j];
	entry[i + j] = '\0';
	return (entry);
}

static int	find_var_index(char *str, char**envp)
{
	
}

int	my_setenv(char *name, char *value, char ***env_ptr)
{
	int		i;
	int		var;
	char	*new_data;

	if (!name || !value || !env_ptr)
		return (-1);
	var = find_var_index(name, *env_ptr);
	new_data = create_env_data(name, value);
}
