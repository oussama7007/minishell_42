/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:55 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/12 16:14:47 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_structs.h"
#include "../built_functions.h"

int	is_valid_identifier(const char *name)
{
	int	i;

	i = 0;
	if (!name || name[0] == '\0' || (!ft_isalpha(name[i]) && name[i] != '_'))
		return (0);
	i++;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// --- Printing Logic (Sorted) ---

void	print_one_export_var(char *env_var_copy)
{
	char	*eq_ptr;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	eq_ptr = ft_strchr(env_var_copy, '=');
	if (eq_ptr)
	{
		*eq_ptr = '\0';
		ft_putstr_fd(env_var_copy, STDOUT_FILENO);
		*eq_ptr = '=';
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(eq_ptr + 1, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	else
		ft_putstr_fd(env_var_copy, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

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

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	if (!envp)
		return (0);
	while (envp[count])
		count++;
	return (count);
}

char	**duplicate_env_for_sort(char **envp, int count, int *error_flag)
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
			free(copy);
			*error_flag = 1;
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

void	free_env_copy(char **env_copy)
{
	int	i;

	i = 0;
	if (!env_copy)
		return ;
	while (env_copy[i])
	{
		free(env_copy[i]);
		i++;
	}
	free(env_copy);
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

// --- Argument Handling ---

void	report_invalid_identifier_err(const char *arg_part)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg_part, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	exec_export_name_only(const char *name_arg, char ***env_ptr)
{
	if (!is_valid_identifier(name_arg))
	{
		report_invalid_identifier_err(name_arg);
		return (1);
	}
	if (!my_getenv(name_arg, *env_ptr))
		return (my_setenv(name_arg, "", env_ptr));
	return (0);
}

int	exec_export_equal(const char *arg, char ***env_ptr)
{
	char	*name;
	char	*value_ptr;
	int		status;

	value_ptr = ft_strchr(arg, '=');
	if (value_ptr == arg)
	{
		report_invalid_identifier_err(arg);
		return (1);
	}
	name = ft_substr(arg, 0, value_ptr - arg);
	if (!name)
		return (1);
	if (!is_valid_identifier(name))
	{
		report_invalid_identifier_err(name);
		free(name);
		return (1);
	}
	status = my_setenv(name, value_ptr + 1, env_ptr);
	free(name);
	return (status);
}

char	*build_appended_value(const char *old_val, const char *val_to_append)
{
	if (!old_val)
		return (ft_strdup(val_to_append));
	return (ft_strjoin(old_val, val_to_append));
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
		free(name);
		return (1);
	}
	val_to_append += 2; // Skip "+=" to get to the value part
	old_val = my_getenv(name, *env_ptr);
	new_val = build_appended_value(old_val, val_to_append);
	if (!new_val)
	{
		free(name);
		return (1);
	}
	status = my_setenv(name, new_val, env_ptr);
	free(name);
	free(new_val);
	return (status);
}

int	process_export_arguments(char **args, char ***env_ptr)
{
	int		i;
	int		ret_status;
	char	*current_arg;
	char	*equal_sign;
	char	*plus_equal_sign;

	i = 1;
	ret_status = 0;
	while (args[i])
	{
		current_arg = args[i];
		plus_equal_sign = ft_strnstr(current_arg, "+=", ft_strlen(current_arg));
		equal_sign = ft_strchr(current_arg, '=');
		if (plus_equal_sign && (plus_equal_sign + 1 == equal_sign))
			ret_status |= exec_export_plus_equal(current_arg, env_ptr);
		else if (equal_sign)
			ret_status |= exec_export_equal(current_arg, env_ptr);
		else
			ret_status |= exec_export_name_only(current_arg, env_ptr);
		i++;
	}
	return (ret_status);
}

int	ft_export(char **args, char ***env_ptr)
{
	if (!env_ptr || !(*env_ptr))
		return (1);
	if (!args[1])
	{
		display_sorted_environment(*env_ptr);
		return (0);
	}
	return (process_export_arguments(args, env_ptr));
}
