/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:44 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/12 16:29:29 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_structs.h"
#include "../built_functions.h"

void	ft_bubble_sort_str_array(char **arr, int count)
{
	int	i;
	int	j;
	int	swapped;

	i = 0;
	while (i < count - 1)
	{
		swapped = 0;
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				ft_swap(&arr[j], &arr[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (swapped == 0)
			break ;
		i++;
	}
}

int	exec_export_plus_equal(const char *arg, char ***env_ptr)
{
	char	*name;
	char	*val_to_append;
	char	*old_val;
	char	*new_val;
	int		status;

	val_to_append = ft_strnstr(arg, "+=", ft_strlen(arg)); // Points to '+'
	name = ft_substr(arg, 0, val_to_append - arg);
	if (!name)
		return (1);
	if (!is_valid_identifier(name))
	{
		report_invalid_identifier_err(name);
		return (free(name), 1);
	}
	val_to_append += 2; // Skip "+=" to get to the value part
	old_val = my_getenv(name, *env_ptr);
	new_val = build_appended_value(old_val, val_to_append);
	if (!new_val)
		return (free(name), 1);
	status = my_setenv(name, new_val, env_ptr);
	return (free(name), free(new_val), status);
}

void	display_sorted_environment(char **envp)
{
	char	**env_copy;
	int		count;
	int		i;
	int		malloc_error;

	count = count_env_vars(envp);
	if (count == 0)
		return ;
	env_copy = duplicate_env_for_sort(envp, count, &malloc_error);
	if (malloc_error || !env_copy)
		return ;
	ft_bubble_sort_str_array(env_copy, count);
	i = 0;
	while (i < count)
	{
		print_one_export_var(env_copy[i]);
		i++;
	}
	free_env_copy(env_copy);
}

char	**duplicate_env_sort(char **envp, int count, int *error_flag)
{
	char	**copy;
	int		i;

	*error_flag = 0;
	copy = (char **)malloc((count + 1) * sizeof(char *));
	if (!copy)
	{
		*error_flag = 1;
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (i-- > 0)
				free(copy[i]);
			*error_flag = 1;
			return (free(copy), NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}
