/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:44 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/12 16:10:42 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_structs.h"
#include "../built_functions.h"

static int	is_valid_identifier(const char *name)
{
	int	i;

	if (!name || !*name || (!ft_isalpha(*name) && *name != '_'))
		return (0);
	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_invalid_identifier(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static void	print_export_var(char *env_var)
{
	char	*eq_ptr;
	int		i;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	eq_ptr = ft_strchr(env_var, '=');
	if (eq_ptr)
	{
		i = 0;
		while (env_var + i < eq_ptr)
			ft_putchar_fd(env_var[i++], STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(eq_ptr + 1, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	else
		ft_putstr_fd(env_var, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	bubble_sort_env(char **env_copy, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(env_copy[j], env_copy[j + 1]) > 0)
			{
				temp = env_copy[j];
				env_copy[j] = env_copy[j + 1];
				env_copy[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static char	**dup_and_sort_env(char **envp)
{
	int		count;
	int		i;
	char	**dup_env;

	count = 0;
	while (envp[count])
		count++;
	dup_env = malloc(sizeof(char *) * (count + 1));
	if (!dup_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup_env[i] = ft_strdup(envp[i]);
		if (!dup_env[i])
		{
			while (--i >= 0)
				free(dup_env[i]);
			free(dup_env);
			return (NULL);
		}
		i++;
	}
	dup_env[count] = NULL;
	return (bubble_sort_env(dup_env, count), dup_env);
}

static void	print_sorted_env(char **envp)
{
	int		i;
	char	**sorted_env;

	sorted_env = dup_and_sort_env(envp);
	if (!sorted_env)
		return;
	i = 0;
	while (sorted_env[i])
	{
		print_export_var(sorted_env[i]);
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}

static int	handle_append(char *arg, char ***env_ptr)
{
	char	*name;
	char	*value;
	char	*eq_ptr;
	char	*old_value;
	char	*new_value;

	eq_ptr = ft_strchr(arg, '=');
	name = ft_strndup(arg, eq_ptr - arg - 1);
	if (!name)
		return (1);
	if (!is_valid_identifier(name))
		return (print_invalid_identifier(arg), free(name), 1);
	value = eq_ptr + 1;
	old_value = my_getenv(name, *env_ptr);
	if (old_value)
	{
		new_value = ft_strjoin(old_value, value);
		if (!new_value)
			return (free(name), 1);
		my_setenv(name, new_value, env_ptr);
		free(new_value);
	}
	else
		my_setenv(name, value, env_ptr);
	return (free(name), 0);
}

static int	handle_name_value(char *arg, char ***env_ptr)
{
	char	*name;
	char	*value;
	char	*eq_ptr;

	eq_ptr = ft_strchr(arg, '=');
	if (eq_ptr == arg)
	{
		print_invalid_identifier(arg);
		return (1);
	}
	if (eq_ptr > arg + 1 && *(eq_ptr - 1) == '+')
		return (handle_append(arg, env_ptr));
	name = ft_strndup(arg, eq_ptr - arg);
	if (!name)
		return (1);
	value = eq_ptr + 1;
	if (!is_valid_identifier(name))
	{
		print_invalid_identifier(arg);
		free(name);
		return (1);
	}
	my_setenv(name, value, env_ptr);
	free(name);
	return (0);
}

static int	handle_name_only(char *arg, char ***env_ptr)
{
	if (!is_valid_identifier(arg))
	{
		print_invalid_identifier(arg);
		return (1);
	}
	if (my_getenv(arg, *env_ptr) == NULL)
		my_setenv(arg, "", env_ptr);
	return (0);
}

int	ft_export(char **args, char ***env_ptr)
{
	int		i;
	int		ret_status;
	char	*eq_ptr;

	ret_status = 0;
	if (!env_ptr || !(*env_ptr))
		return (1);
	if (!args[1])
	{
		print_sorted_env(*env_ptr);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		eq_ptr = ft_strchr(args[i], '=');
		if (eq_ptr)
			ret_status |= handle_name_value(args[i], env_ptr);
		else
			ret_status |= handle_name_only(args[i], env_ptr);
		i++;
	}
	return (ret_status);
}
