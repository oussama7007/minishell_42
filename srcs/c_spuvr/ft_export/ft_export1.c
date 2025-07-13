/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:55 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/13 00:56:29 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

void	clean_two_strings(char *str1, char *str2)
{
	free(str1);
	free(str2);
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
