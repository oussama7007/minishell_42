/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mytest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/09 16:43:26 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h"
#include "built_functions.h"

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

int main(int ac, char **av, char **env)
{
	char	**my_envp;
	(void)ac;
	(void)av;

	my_envp = init_environment(env);
	if (!my_envp)
	{
		write(2, "Error: Failed to initialize environment\n", 40);
		return (1);
	}
	free_environment(my_envp);
	return (0);
}
