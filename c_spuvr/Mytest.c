/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mytest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/05 17:34:35 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h" // <-- Needs the structures we just defined
#include <stdio.h>            // For printf, basic stuff
#include <stdlib.h>           // For malloc, free, exit
#include <unistd.h>           // For write, access, chdir, fork, execve, etc.

// Forward declare the first function you're gonna build
char    **init_environment(char **system_envp);

int main(int ac, char **av, char **env)
{
    char **my_shell_envp; // This will hold YOUR shell's copy of the env vars

    (void)ac; // Shut up compiler warnings for now
    (void)av; // Shut up compiler warnings for now

    // --- Your VERY FIRST STEP ---
    // Before you can run commands, handle 'cd', 'export', 'unset', or even find
    // external commands using PATH, your shell needs its OWN copy of the environment
    // variables. You CANNOT directly modify the 'env' passed to main, that's bad practice
    // and might break things. You need a deep copy.
    //
    // Function to build: init_environment
    // What it does:    Takes the system environment ('env' from main) and creates
    //                  a NEW, dynamically allocated array of strings (char **)
    //                  containing copies of every single string from the original 'env'.
    //                  This is YOUR shell's private environment.
    // How to build it: Count how many strings are in 'env' (it's NULL terminated).
    //                  Allocate memory for a new char ** array of that size + 1 (for the NULL).
    //                  Loop through 'env'. For each string, duplicate it using strdup()
    //                  (or your own equivalent) and store the pointer to the duplicate
    //                  in your new array.
    //                  Make sure the last element of your new array is NULL.
    // What it takes:   It takes one argument: `char **system_envp` (which is the 'env' from main).
    // What it returns: It returns the pointer to the NEWLY allocated `char **` array (your copy).
    //                  It should return NULL if any allocation fails.
    // Why first?:      Almost everything else depends on having the environment accessible
    //                  and modifiable (PATH for finding commands, PWD/OLDPWD for cd,
    //                  HOME for cd, etc.). Get this right first.
    //
    my_shell_envp = init_environment(env);
    if (!my_shell_envp)
    {
        // Use write(2, ...) for error messages in a shell, not printf
        write(2, "Error: Failed to initialize environment\n", 40);
        return (1); // Exit if we can't even setup the env
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

// --- Function Implementations Go Here (or in other .c files) ---

// You will implement this function now:
// char **init_environment(char **system_envp) {
//     // ... your code to count, malloc, loop, strdup, null-terminate ...
// }