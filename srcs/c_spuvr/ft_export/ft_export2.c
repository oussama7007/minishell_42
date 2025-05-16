/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:37:18 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/16 14:15:02 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

int	handle_plus_equal_error(const char *plus_equal_ptr, char *name)
{
	char	*val_for_err;
	char	*err_str;

	val_for_err = strip_outer_quotes(plus_equal_ptr + 2);
	if (!val_for_err)
	{
		free(name);
		return (1);
	}
	err_str = ft_strjoin("+=", val_for_err);
	if (!err_str)
	{
		free(val_for_err);
		free(name);
		return (1);
	}
	print_err_export(NULL, err_str);
	free(val_for_err);
	free(err_str);
	free(name);
	return (1);
}

int	create_append_value(char *name, char *append_val, char ***env_ptr)
{
	char	*old_val;
	char	*new_val_str;
	int		status;

	old_val = my_getenv(name, *env_ptr);
	if (!old_val)
		new_val_str = ft_strdup(append_val);
	else
		new_val_str = ft_strjoin(old_val, append_val);
	if (!new_val_str)
		return (1);
	status = my_setenv(name, new_val_str, env_ptr);
	free(new_val_str);
	return (status);
}

int	exec_export_plus_equal(const char *arg, char ***env_ptr)
{
	char	*name;
	char	*plus_equal_ptr;
	char	*stripped_value;
	int		status;

	plus_equal_ptr = ft_strnstr(arg, "+=", ft_strlen(arg));
	name = ft_substr(arg, 0, plus_equal_ptr - arg);
	if (!name)
		return (1);
	if (name[0] == '\0')
		return (handle_plus_equal_error(plus_equal_ptr, name));
	if (!is_valid_identifier(name))
	{
		print_err_export(NULL, name);
		free(name);
		return (1);
	}
	stripped_value = strip_outer_quotes(plus_equal_ptr + 2);
	if (!stripped_value)
	{
		free(name);
		return (1);
	}
	status = create_append_value(name, stripped_value, env_ptr);
	free(name);
	free(stripped_value);
	return (status);
}
