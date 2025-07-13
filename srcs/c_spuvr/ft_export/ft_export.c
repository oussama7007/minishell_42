/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:44 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/13 00:56:25 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static int	parse_export_arg(const char *arg, char **name,
		char **value, int *is_append)
{
	char	*eq_sign;
	int		name_len;

	*name = NULL;
	*value = NULL;
	*is_append = 0;
	eq_sign = ft_strchr(arg, '=');
	if (!eq_sign)
	{
		*name = ft_strdup(arg);
		return (0);
	}
	if (eq_sign > arg && *(eq_sign - 1) == '+')
	{
		*is_append = 1;
		name_len = (eq_sign - 1) - arg;
	}
	else
		name_len = eq_sign - arg;
	*name = ft_substr(arg, 0, name_len);
	*value = ft_strdup(eq_sign + 1);
	if (!*name || !*value)
		return (free(*name), free(*value), 1);
	return (0);
}

static int	execute_export_assignment(char *name, char *value,
		int is_append, char ***env_ptr)
{
	char	*stripped_value;
	int		status;

	stripped_value = strip_outer_quotes(value);
	if (!stripped_value)
		return (1);
	if (is_append)
		status = create_append_value(name, stripped_value, env_ptr);
	else
		status = my_setenv(name, stripped_value, env_ptr);
	free(stripped_value);
	return (status);
}

int	exec_export_name_only(const char *name_arg, char ***env_ptr)
{
	char	*pwd_buffer;

	if (!name_arg || name_arg[0] == '\0')
		return (print_err_export(NULL, name_arg), 1);
	if (!is_valid_identifier(name_arg))
		return (print_err_export(NULL, name_arg), 1);
	if (ft_strcmp((char *)name_arg, "PWD") == 0)
	{
		pwd_buffer = getcwd(NULL, 0);
		if (pwd_buffer)
		{
			my_setenv("PWD", pwd_buffer, env_ptr);
			free(pwd_buffer);
		}
		return (0);
	}
	if (!my_getenv(name_arg, *env_ptr))
		return (my_setenv((char *)name_arg, NULL, env_ptr));
	return (0);
}

static int	handle_single_export_arg(char *arg, char ***env_ptr)
{
	char	*name;
	char	*value;
	int		is_append;
	int		status;

	if (ft_strcmp(arg, "export") == 0)
	{
		print_err_export(NULL, arg);
		return (1);
	}
	if (parse_export_arg(arg, &name, &value, &is_append) != 0)
		return (2);
	status = 0;
	if (!is_valid_identifier(name))
	{
		print_err_export(NULL, arg);
		status = 1;
	}
	else if (value)
		status = execute_export_assignment(name, value, is_append, env_ptr);
	else
		status = exec_export_name_only(name, env_ptr);
	clean_two_strings(name, value);
	return (status);
}

int	process_export_arguments(char **args, char ***env_ptr)
{
	int	i;
	int	ret_status;
	int	arg_status;

	i = 1;
	ret_status = 0;
	while (args[i])
	{
		arg_status = handle_single_export_arg(args[i], env_ptr);
		if (arg_status == 2)
			return (1);
		ret_status |= arg_status;
		i++;
	}
	return (ret_status);
}
