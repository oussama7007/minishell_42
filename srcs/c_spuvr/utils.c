/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:08:03 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/03 15:50:11 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

char	*create_env_data(char *name, char *value)
{
	int		n_len;
	int		v_len;
	char	*entry;

	n_len = ft_strlen(name);
	v_len = ft_strlen(value);
	if (value == NULL)
	{
		entry = malloc (n_len + 1);
		if (!entry)
			return (NULL);
		ft_strlcpy(entry, name, n_len + 1);
	}
	else
	{
		entry = malloc(n_len + v_len + 2);
		if (!entry)
			return (NULL);
		ft_strlcpy(entry, name, n_len + 1);
		entry[n_len] = '=';
		ft_strlcpy(entry + n_len + 1, value, v_len + 1);
	}
	return (entry);
}

int	find_var_index(const char *name_to_find, char **envp)
{
	int	i;
	int	name_len;

	if (!name_to_find || !envp || name_to_find[0] == '\0')
		return (-1);
	name_len = 0;
	while (name_to_find[name_len])
		name_len++;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name_to_find, name_len) == 0)
		{
			if (envp[i][name_len] == '\0' || envp[i][name_len] == '=')
			{
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

char	**init_environment(char **system_envp)
{
	int		i;
	int		count;
	char	**copy;

	count = 0;
	while (system_envp[count])
		count++;
	copy = malloc((count + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(system_envp[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

void	free_environment(char **envp_ptr)
{
	int	j;

	if (!envp_ptr)
		return ;
	j = ft_arrlen(envp_ptr);
	while (j >= 0)
	{
		free(envp_ptr[j]);
		j--;
	}
	free(envp_ptr);
}
