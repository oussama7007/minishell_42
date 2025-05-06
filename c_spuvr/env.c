/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:00:09 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/06 16:00:39 by oadouz           ###   ########.fr       */
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

