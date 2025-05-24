/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:45 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/24 18:24:20 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

// int ft_chdir(char **args, char ***env_ptr)
// {
//     char *target_path;
//     char *old_pwd = NULL;
//     char *new_pwd = NULL;
//     int ret = 0;
    
//     // Get current working directory for OLDPWD before changing it
//     old_pwd = getcwd(NULL, 0);
//     if (!old_pwd)
//     {
//         ft_putstr_fd("minishell: cd: error retrieving current directory: ", 2);
//         ft_putendl_fd(strerror(errno), 2);
//         // Continue anyway - we'll just have an empty OLDPWD if this fails
//     }

//     // Determine target path based on arguments
//     if (!args[1] || args[1][0] == '\0')
//     {
//         // Case 1: No args or empty string - go to HOME
//         target_path = my_getenv("HOME", *env_ptr);
//         if (!target_path || target_path[0] == '\0')
//         {
//             ft_putendl_fd("minishell: cd: HOME not set", 2);
//             free(old_pwd); // Free here before early return
//             return (1);
//         }
//     }
//     else if (ft_strcmp(args[1], "-") == 0)
//     {
//         // Case 2: cd - (go to OLDPWD)
//         target_path = my_getenv("OLDPWD", *env_ptr);
//         if (!target_path || target_path[0] == '\0')
//         {
//             ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
//             free(old_pwd); // Free here before early return
//             return (1);
//         }
//         // Print the directory we're changing to when using 'cd -'
//         ft_putendl_fd(target_path, 1);
//     }
//     else
//     {
//         // Case 3: cd to specified path
//         target_path = args[1];
//     }
    
//     // Attempt to change directory
//     ret = chdir(target_path);
//     if (ret == -1)
//     {
//         ft_putstr_fd("minishell: cd: ", 2);
//         ft_putstr_fd(target_path, 2);
//         ft_putstr_fd(": ", 2);
//         ft_putendl_fd(strerror(errno), 2);
//         free(old_pwd); // Free here before early return
//         return (1);
//     }
    
//     // Successfully changed directory, now update environment variables
    
//     // 1. Set OLDPWD to the old path
//     if (old_pwd)
//     {
//         if (my_setenv("OLDPWD", old_pwd, env_ptr) != 0)
//         {
//             ft_putendl_fd("minishell: cd: failed to update OLDPWD", 2);
//             // Non-fatal error, continue
//         }
//     }
    
//     // 2. Get new PWD and update it
//     new_pwd = getcwd(NULL, 0);
//     if (!new_pwd)
//     {
//         ft_putstr_fd("minishell: cd: error retrieving new directory: ", 2);
//         ft_putendl_fd(strerror(errno), 2);
//         free(old_pwd); // Free old_pwd here ONLY - removed the duplicate free
//         return (0);    // Still return success as cd worked
//     }
    
//     if (my_setenv("PWD", new_pwd, env_ptr) != 0)
//     {
//         ft_putendl_fd("minishell: cd: failed to update PWD", 2);
//         // Non-fatal
//     }
    
//     // Free allocated memory
//     free(old_pwd);
//     free(new_pwd);
//     return (0); // Success
// }
