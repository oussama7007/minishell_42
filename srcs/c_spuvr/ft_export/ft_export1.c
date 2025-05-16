/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:55 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/16 14:14:58 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

int	handle_equal_start(const char *value_ptr, int *status)
{
	char	*val_for_err;
	char	*err_str;

	val_for_err = strip_outer_quotes(value_ptr + 1);
	if (!val_for_err)
		return (1);
	err_str = ft_strjoin("=", val_for_err);
	if (!err_str)
	{
		free(val_for_err);
		return (1);
	}
	print_err_export(NULL, err_str);
	free(val_for_err);
	free(err_str);
	*status = 1;
	return (1);
}

int	exec_export_value(const char *arg, char ***env_ptr)
{
	char	*name;
	char	*value_ptr;
	char	*stripped_value;
	int		status;

	status = 0;
	value_ptr = ft_strchr(arg, '=');
	if (value_ptr == arg)
		return (handle_equal_start(value_ptr, &status));
	name = ft_substr(arg, 0, value_ptr - arg);
	if (!name)
		return (1);
	if (!is_valid_identifier(name))
	{
		print_err_export(NULL, name);
		free(name);
		return (1);
	}
	stripped_value = strip_outer_quotes(value_ptr + 1);
	if (!stripped_value)
	{
		free(name);
		return (1);
	}
	status = my_setenv(name, stripped_value, env_ptr);
	free(name);
	free(stripped_value);
	return (status);
}
