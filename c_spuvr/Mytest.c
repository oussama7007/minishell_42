/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mytest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/05 18:26:14 by oadouz           ###   ########.fr       */
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

int main(int ac, char **av, char **env)
{
	char	**copy_envp;
	int i = 0;
	int j = 0;
	(void)ac;
	(void)av;

    copy_envp = init_environment(env);
	if (!copy_envp)
	{
	    write(2, "Error: Failed to initialize environment\n", 40);
	    return (1);
	}

	while(copy_envp[j])
	{
		i = 0;
		while(copy_envp[j][i])
		{
			write(1, &copy_envp[j][i], 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
	return (0);
}
