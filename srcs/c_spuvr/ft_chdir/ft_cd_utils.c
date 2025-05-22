// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_cd_utils.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/15 17:04:43 by oadouz            #+#    #+#             */
// /*   Updated: 2025/05/21 17:38:48 by oadouz           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// // Helper function you'll need to write (can be in ft_cd_utils.c)
// // Joins base and rel. If rel is absolute, it returns a copy of rel.
// // If base is NULL and rel is relative, it might return copy of rel or NULL.
// // This simplified version just concatenates for relative paths, mimicking bash's PWD display.
// // A more robust one would normalize ".." and "." within the string.
// static char *construct_logical_path(const char *base_pwd, const char *target_arg)
// {
//     char *new_path;
//     char *temp;

//     if (!target_arg) return (NULL);
//     if (target_arg[0] == '/') // target_arg is absolute
//         return (ft_strdup(target_arg));

//     if (!base_pwd || *base_pwd == '\0') // No base to append to
//         return (ft_strdup(target_arg));

//     // Relative path: append target_arg to base_pwd
//     // Ensure one slash between base_pwd and target_arg
//     temp = ft_strjoin(base_pwd, "/");
//     if (!temp) return NULL;
//     new_path = ft_strjoin(temp, target_arg);
//     free(temp);
//     return (new_path); // Caller must free this
//     // Example: base="/a/b", target="c" -> "/a/b/c"
//     // Example: base="/a/b", target=".." -> "/a/b/.." (bash style for PWD)
// }

// int ft_chdir(char **args, char ***env_ptr)
// {
//     char *target_path_arg; // The argument to cd (e.g., "..", "foo", "/abs/path")
//     char *current_env_pwd_before_cd = NULL;
//     char *old_pwd_for_env = NULL;
//     char *new_env_pwd_value = NULL;
//     int chdir_ret = 0;

//     // 1. Determine current PWD for OLDPWD
//     // Prefer getenv("PWD") as the most up-to-date PWD from the shell's perspective
//     current_env_pwd_before_cd = my_getenv("PWD", *env_ptr);
//     if (current_env_pwd_before_cd && *current_env_pwd_before_cd)
//     {
//         old_pwd_for_env = ft_strdup(current_env_pwd_before_cd);
//         // No free for current_env_pwd_before_cd if my_getenv returns a direct pointer
//     }
//     else // Fallback if PWD is not in env
//     {
//         old_pwd_for_env = getcwd(NULL, 0);
//         if (!old_pwd_for_env)
//         {
//             ft_putstr_fd("minishell: cd: error retrieving current directory for OLDPWD: ", 2);
//             ft_putendl_fd(strerror(errno), 2);
//             // old_pwd_for_env remains NULL, OLDPWD might not be set
//         }
//     }

//     // 2. Determine target_path_arg based on args[1]
//     if (!args[1] || args[1][0] == '\0')
//     {
//         target_path_arg = my_getenv("HOME", *env_ptr);
//         if (!target_path_arg || target_path_arg[0] == '\0')
//         {
//             ft_putendl_fd("minishell: cd: HOME not set", 2);
//             free(old_pwd_for_env);
//             return (1);
//         }
//         // target_path_arg now points to HOME value, no need to free if it's from my_getenv directly
//     }
//     else if (ft_strcmp(args[1], "-") == 0)
//     {
//         target_path_arg = my_getenv("OLDPWD", *env_ptr);
//         if (!target_path_arg || target_path_arg[0] == '\0')
//         {
//             ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
//             free(old_pwd_for_env);
//             return (1);
//         }
//         ft_putendl_fd(target_path_arg, 1); // Print directory when using 'cd -'
//     }
//     else
//     {
//         target_path_arg = args[1];
//     }

//     // 3. Attempt to change directory
//     chdir_ret = chdir(target_path_arg);
//     if (chdir_ret == -1)
//     {
//         ft_putstr_fd("minishell: cd: ", 2);
//         ft_putstr_fd(target_path_arg, 2); // Use target_path_arg here
//         ft_putstr_fd(": ", 2);
//         ft_putendl_fd(strerror(errno), 2);
//         free(old_pwd_for_env);
//         return (1);
//     }

//     // 4. Successfully changed directory, now update PWD and OLDPWD environment variables

//     // 4a. Set OLDPWD
//     if (old_pwd_for_env)
//     {
//         my_setenv("OLDPWD", old_pwd_for_env, env_ptr);
//     }
//     free(old_pwd_for_env); // Free the string we prepared for OLDPWD

//     // 4b. Determine new PWD value
//     char *real_new_pwd_from_getcwd = getcwd(NULL, 0);
//     if (real_new_pwd_from_getcwd)
//     {
//         new_env_pwd_value = real_new_pwd_from_getcwd; // This is the canonical path
//     }
//     else
//     {
//         // getcwd failed! Construct logical PWD.
//         ft_putstr_fd("minishell: cd: error retrieving new directory: ", 2); // Keep this error
//         ft_putendl_fd(strerror(errno), 2);                             // But still update PWD logically

//         // Use current_env_pwd_before_cd (what PWD *was*) as the base for relative paths.
//         // If PWD wasn't set, old_pwd_for_env (from initial getcwd) could be a fallback base.
//         char *base_for_logical_pwd = my_getenv("PWD", *env_ptr); // Re-fetch PWD to use the value just before this chdir
//                                                                   // (which was just moved to OLDPWD if it existed)

//         new_env_pwd_value = construct_logical_path(base_for_logical_pwd, target_path_arg);
//         // No free for base_for_logical_pwd if it's from my_getenv direct pointer
//     }

//     // 4c. Set PWD
//     if (new_env_pwd_value)
//     {
//         if (my_setenv("PWD", new_env_pwd_value, env_ptr) != 0)
//         {
//             ft_putendl_fd("minishell: cd: failed to update PWD", 2);
//         }
//         free(new_env_pwd_value); // Free the string we prepared for PWD
//     }
//     else
//     {
//         // Should not happen if construct_logical_path is robust or getcwd worked
//         ft_putendl_fd("minishell: cd: PWD could not be determined", 2);
//     }
    
//     return (0); // Success
// }
