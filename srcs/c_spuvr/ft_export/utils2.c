/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:40:41 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/10 21:57:32 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	ms_sort_env_array(char **arr_to_sort, int count)
{
	int		i;
	int		j;
	int		sorted;

	if (!arr_to_sort || count <= 1)
		return ;
	i = 0;
	while (i < count - 1)
	{
		sorted = 1;
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strcmp(arr_to_sort[j], arr_to_sort[j + 1]) > 0)
			{
				swap_strings(&arr_to_sort[j], &arr_to_sort[j + 1]);
				sorted = 0;
			}
			j++;
		}
		if (sorted)
			break ;
		i++;
	}
}

static char	**ms_duplicate_env(char **original_env, int count)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(original_env[i]);
		if (!new_env[i])
		{
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
	int	i;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	i = 0;
	while (env_str[i] && env_str[i] != '=')
	{
		ft_putchar_fd(env_str[i], STDOUT_FILENO);
		i++;
	}
	if (env_str[i] == '=')
	{
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		i++;
		while (env_str[i])
		{
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
		return ;
	count = ft_arrlen(envp);
	if (count == 0)
		return ;
	env_copy = ms_duplicate_env(envp, count);
	if (!env_copy)
		return ;
	ms_sort_env_array(env_copy, count);
	i = 0;
	while (i < count)
	{
		if (ft_strncmp(env_copy[i], "_=", 2) != 0)
			ms_print_one_env_declare(env_copy[i]);
		free(env_copy[i]);
		i++;
	}
	free(env_copy);
}
