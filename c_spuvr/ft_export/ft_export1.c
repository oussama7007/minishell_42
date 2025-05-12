/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:55 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/12 17:06:23 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_structs.h"
#include "../built_functions.h"

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

int	exec_export_name_only(const char *name_arg, char ***env_ptr)
{
	if (!is_valid_identifier(name_arg))
	{
		print_err_111(name_arg);
		return (1);
	}
	if (!my_getenv(name_arg, *env_ptr))
		return (my_setenv((char *)name_arg, "", env_ptr));
	return (0);
}

int	exec_export_value(const char *arg, char ***env_ptr)
{
	char	*name;
	char	*value_ptr;
	int		status;

	value_ptr = ft_strchr(arg, '=');
	if (value_ptr == arg)
	{
		print_err_111(arg);
		return (1);
	}
	name = ft_substr(arg, 0, value_ptr - arg);
	if (!name)
		return (1);
	if (!is_valid_identifier(name))
	{
		print_err_111(name);
		free(name);
		return (1);
	}
	status = my_setenv(name, value_ptr + 1, env_ptr);
	free(name);
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
			ret_status |= exec_export_value(current_arg, env_ptr);
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
