/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:44 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/14 18:27:12 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_structs.h"
#include "../built_functions.h"

int	exec_export_name_only(const char *name_arg, char ***env_ptr)
{
	if (!name_arg || name_arg[0] == '\0' || ft_strchr(name_arg, '='))
	{
		print_err_export(NULL, name_arg);
		return (1);
	}
	if (!my_getenv(name_arg, *env_ptr))
	{
		return (my_setenv((char *)name_arg, NULL, env_ptr));
	}
	return (0);
}
