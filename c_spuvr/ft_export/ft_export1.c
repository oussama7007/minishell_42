/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:55 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/12 15:27:50 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_structs.h"
#include "../built_functions.h"

int	handle_name_only(char *arg, char ***env_ptr)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	if (!my_getenv(arg, *env_ptr))
		return (my_setenv(arg, "", env_ptr));
	return (0);
}

// print error 
void	export_print_1(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

//print error
static int	handle_name_value(char *arg, char ***env_ptr)
{
	char	*eq_ptr;
	char	*name;
	int		status;

	eq_ptr = ft_strchr(arg, '=');
	if (eq_ptr == arg)
		return (export_print_1(arg), 1);
	name = ft_strdup(arg);
	if (!name)
		return (1);
	name[eq_ptr - arg] = '\0';
	if (!is_valid_identifier(name))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		free(name);
		return (1);
	}
	status = my_setenv(name, eq_ptr + 1, env_ptr);
	return (free(name), status);
}
