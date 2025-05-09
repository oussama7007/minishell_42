/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:08:03 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/08 16:28:14 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h"

char	*create_env_data(char *name, char *value)
{
	int		n_len;
	int		v_len;
	char	*entry;

	n_len = ft_strlen(name);
	v_len = ft_strlen(value);
	// Allocate memory for "name=value\0" string  || // +1 for '=', +1 for '\0'
	entry = malloc(n_len + v_len + 2);
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
