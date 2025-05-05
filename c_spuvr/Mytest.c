/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mytest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/05 18:18:10 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h" // <-- Needs the structures we just defined
#include <stdio.h>            // For printf, basic stuff
#include <stdlib.h>           // For malloc, free, exit
#include <unistd.h>           // For write, access, chdir, fork, execve, etc.

// Forward declare the first function you're gonna build
char	**init_environment(char **system_envp)
{
	int		i;
	int		count;
	char	**copy;

	count = 0;
	while (system_envp[count])
		count++;
	copy = malloc()
}

int main(int ac, char **av, char **env)
{
	char	**copy_envp;
	
	(void)ac;
	(void)av;

    my_shell_envp = init_environment(env);
	if (!my_shell_envp)
	{
	    write(2, "Error: Failed to initialize environment\n", 40);
	    return (1);
	}

	// For now, just print a message to show it worked (or seemed to)
	printf("DEBUG: Shell environment initialized.\n");

	// Later, your main loop (readline, parse, execute) will go here...
	// while (1) { ... }
	
	// --- Cleanup ---
	// Eventually, you'll need a function to free the memory allocated by init_environment
	// free_environment(my_shell_envp); // Build this function later

	return (0);
}
