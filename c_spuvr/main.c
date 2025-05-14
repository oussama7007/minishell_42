/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mytest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/13 13:51:03 by oadouz           ###   ########.fr       */
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

char **simple_ft_split(char *str) {
    int i = 0;
    int j = 0;
    int k = 0;
    int wc = 0;
    char **out;

    if (!str) return NULL;
    while (str[i]) { // Count words
        while (str[i] && (str[i] == ' ' || str[i] == '\t')) i++;
        if (str[i]) wc++;
        while (str[i] && str[i] != ' ' && str[i] != '\t') i++;
    }
    out = (char **)malloc(sizeof(char *) * (wc + 1));
    if (!out) return NULL;
    i = 0;
    while (str[i] && j < wc) {
        while (str[i] && (str[i] == ' ' || str[i] == '\t')) i++;
        if (str[i]) {
            k = i;
            while (str[i] && str[i] != ' ' && str[i] != '\t') i++;
            out[j] = ft_substr(str, k, i - k); // Assuming ft_substr
            if (!out[j]) { /* memory error, free out[0]..out[j-1] and out */ return NULL; }
            j++;
        }
    }
    out[j] = NULL;
    return out;
}

void free_split_args(char **args) {
    int i = 0;
    if (!args) return;
    while(args[i]) {
        free(args[i]);
        i++;
    }
    free(args);
}


int main(int ac, char **av, char **env)
{
	char	**my_envp;
	char	*line_read;
	char	**args;
	int		exit_status;

	(void)ac;
	(void)av;
	exit_status = 0;
	my_envp = init_environment(env);
	if (!my_envp)
	{
		ft_putstr_fd("Error: Failed to initialize environment\n", STDERR_FILENO);
		return (1);
	}
	if (!my_envp)
	{
		write(2, "Error: Failed to initialize environment\n", 40);
		return (1);
	}
	while (1)
	{
		line_read = readline("minishell-test> ");
		if (!line_read) // NULL on EOF (Ctrl+D)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (line_read[0]) // If line is not empty
			add_history(line_read);

		args = simple_ft_split(line_read); // Use your real ft_split
		
		if (args && args[0])
		{
			if (ft_strcmp(args[0], "export") == 0)
			{
				exit_status = ft_export(args, &my_envp);
				// printf("export status: %d\n", exit_status); // Optional debug
			}
			else if (ft_strcmp(args[0], "echo") == 0)
			{
                ft_echo(args);
            }
			else if (ft_strcmp(args[0], "exit") == 0)
			{
				free(line_read);
				free_split_args(args);
				break;
			}
			// Add other commands like 'unset' here for thorough testing
			else if (args[0][0] != '\0') // If not an empty command
			{
				ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
				ft_putstr_fd(args[0], STDERR_FILENO);
				ft_putchar_fd('\n', STDERR_FILENO);
				exit_status = 127;
			}
		}
		free(line_read);
		free_split_args(args);
	}
	free_environment(my_envp);
	return (exit_status);
}
