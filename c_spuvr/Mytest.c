/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mytest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/06 15:14:00 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h"

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
			return(NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

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
		if (ft_strncmp(envp[i], name, n_len) == 0 && envp[i][n_len + 1] == '=')
			return (&envp[i][n_len + 1]);
		i++;
	}
	return (NULL);
}

int main(int ac, char **av, char **env)
{
	char	**copy_envp;
	(void)ac;
	(void)av;

    copy_envp = init_environment(env);
	if (!copy_envp)
	{
	    write(2, "Error: Failed to initialize environment\n", 40);
	    return (1);
	}
	
	return (0);
}
