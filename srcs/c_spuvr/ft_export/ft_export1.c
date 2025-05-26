/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:55 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/25 19:32:34 by oait-si-         ###   ########.fr       */
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

// #include "../built_functions.h"

// int	handle_equal_start(t_head_list *head,const char *value_ptr, int *status)
// {
// 	char	*val_for_err;
// 	char	*err_str;

// 	val_for_err = strip_outer_quotes(head, value_ptr + 1);
// 	if (!val_for_err)
// 		return (1);
// 	err_str = ft_strjoin(head,"=", val_for_err);
// 	if (!err_str)
// 	{
// 		free_gc(head);
// 		return (1);
// 	}
// 	print_err_export(NULL, err_str);
// 	//free(val_for_err);
// 	//free(err_str);
// 	*status = 1;
// 	return (1);
// }

// int	exec_export_value(t_head_list *head,const char *arg, char ***env_ptr)
// {
// 	char	*name;
// 	char	*value_ptr;
// 	char	*stripped_value;
// 	int		status;

// 	status = 0;
// 	value_ptr = ft_strchr(arg, '=');
// 	if (value_ptr == arg)
// 		return (handle_equal_start(head, value_ptr, &status));
// 	name = ft_substr(head,arg, 0, value_ptr - arg);
// 	if (!name)
// 		return (1);
// 	if (!is_valid_identifier(name))
// 	{
// 		print_err_export(NULL, name);
// 		free_gc(head);
// 		return (1);
// 	}
// 	stripped_value = strip_outer_quotes(head,value_ptr + 1);
// 	if (!stripped_value)
// 	{
// 		free_gc(head);
// 		return (1);
// 	}
// 	status = my_setenv(head,name, stripped_value, env_ptr);
// 	//free(name);
// 	//free(stripped_value);
// 	return (status);
// }
