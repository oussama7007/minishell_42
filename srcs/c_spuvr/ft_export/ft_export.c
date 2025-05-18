/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:44 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/18 15:19:18 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

int	is_standalone_name(const char *arg)
{
	if (!arg || !*arg)
		return (0);
	return (!ft_strchr(arg, '=') && !ft_strnstr(arg, "+=", ft_strlen(arg)));
}

int	exec_export_name_only(const char *name_arg, char ***env_ptr)
{
	if (!name_arg || name_arg[0] == '\0')
	{
		print_err_export(NULL, name_arg);
		return (1);
	}
	if (!is_valid_identifier(name_arg))
	{
		print_err_export(NULL, name_arg);
		return (1);
	}
	if (!my_getenv(name_arg, *env_ptr))
		return (my_setenv((char *)name_arg, NULL, env_ptr));
	return (0);
}

int	process_export_arguments(char **args, char ***env_ptr)
{
	int		i;
	int		ret_status;
	char	*current_arg;

	i = 1;
	ret_status = 0;
	while (args[i])
	{
		current_arg = args[i];
		if (is_standalone_name(current_arg))
			ret_status |= exec_export_name_only(current_arg, env_ptr);
		else if (ft_strnstr(current_arg, "+=", ft_strlen(current_arg)))
			ret_status |= exec_export_plus_equal(current_arg, env_ptr);
		else if (ft_strchr(current_arg, '='))
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
