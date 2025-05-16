/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/16 14:13:57 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

// int main(int ac, char **av, char **env)
// {
// 	char	**my_envp;
// 	char	*line_read;
// 	char	**args;
// 	int		exit_status;

// 	(void)ac;
// 	(void)av;
// 	exit_status = 0;
// 	my_envp = init_environment(env);
// 	if (!my_envp)
// 	{
// 		ft_putstr_fd("Error: Failed to initialize environment\n", STDERR_FILENO);
// 		return (1);
// 	}
// 	if (!my_envp)
// 	{
// 		write(2, "Error: Failed to initialize environment\n", 40);
// 		return (1);
// 	}
// 	while (1)
// 	{
// 		line_read = readline("minishell-test> ");
// 		if (!line_read) // NULL on EOF (Ctrl+D)
// 		{
// 			ft_putstr_fd("exit\n", STDOUT_FILENO);
// 			break ;
// 		}
// 		if (line_read[0]) // If line is not empty
// 			add_history(line_read);		
// 		if (args && args[0])
// 		{
// 			if (ft_strcmp(args[0], "export") == 0)
// 			{
// 				exit_status = ft_export(args, &my_envp);
// 				// printf("export status: %d\n", exit_status); // Optional debug
// 			}
// 			else if (ft_strcmp(args[0], "exit") == 0)
// 			{
// 				free(line_read);
// 				free_split_args(args);
// 				break;
// 			}
// 			// Add other commands like 'unset' here for thorough testing
// 			else if (args[0][0] != '\0') // If not an empty command
// 			{
// 				ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
// 				ft_putstr_fd(args[0], STDERR_FILENO);
// 				ft_putchar_fd('\n', STDERR_FILENO);
// 				exit_status = 127;
// 			}
// 		}
// 		free(line_read);
// 		free_split_args(args);
// 	}
// 	free_environment(my_envp);
// 	return (exit_status);
// }
