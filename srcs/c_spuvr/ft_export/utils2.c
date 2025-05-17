/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:40:41 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/17 15:51:53 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static void	ms_sort_env_array(char **arr_to_sort, int count)
{
	int		i;
	int		j;
	char	*temp;
	int		sorted;

	if (!arr_to_sort || count <= 1)
		return;
	i = 0;
	while (i < count - 1)
	{
		sorted = 1;
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strcmp(arr_to_sort[j], arr_to_sort[j + 1]) > 0)
			{
				temp = arr_to_sort[j];
				arr_to_sort[j] = arr_to_sort[j + 1];
				arr_to_sort[j + 1] = temp;
				sorted = 0;
			}
			j++;
		}
		if (sorted) // Optimization: if no swaps in a pass, it's sorted
			break;
		i++;
	}
}

static char	**ms_duplicate_env(char **original_env, int count)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL); // Malloc error
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(original_env[i]);
		if (!new_env[i])
		{
			// Malloc error during strdup, free previously duplicated strings
			while (i > 0)
			{
				i--;
				free(new_env[i]);
			}
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

static void	ms_print_one_env_declare(char *env_str)
{
	int		i;
	// int		has_equal_sign;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	i = 0;
	// has_equal_sign = 0;
	while (env_str[i] && env_str[i] != '=')
	{
		ft_putchar_fd(env_str[i], STDOUT_FILENO);
		i++;
	}
	if (env_str[i] == '=')
	{
		// has_equal_sign = 1;
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		i++; // Skip '='
		while (env_str[i])
		{
			// Basic quoting for a double quote inside the value.
			// Bash does more extensive escaping, this is a simplification.
			if (env_str[i] == '"')
				ft_putstr_fd("\\\"", STDOUT_FILENO);	
			else
				ft_putchar_fd(env_str[i], STDOUT_FILENO);
			i++;
		}
		ft_putchar_fd('"', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	display_sorted_environment(char **envp)
{
	char	**env_copy;
	int		count;
	int		i;

	if (!envp)
		return;
	count = ft_arrlen(envp);
	if (count == 0)
		return;
	env_copy = ms_duplicate_env(envp, count);
	if (!env_copy)
	{
		return;
	}
	ms_sort_env_array(env_copy, count);
	i = 0;
	while (i < count)
	{
		ms_print_one_env_declare(env_copy[i]);
		free(env_copy[i]); // Free the strduped string
		i++;
	}
	free(env_copy); // Free the array of pointers
}
