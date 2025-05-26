/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:43 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/25 18:46:00 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

char	*target_path(char **args, char **envp)
{
	char	*path;

	if (!args[1] || args[1][0] == '\0')
	{
		path = my_getenv("HOME", envp);
		if (!path || path[0] == '\0')
			return (ft_putstr_fd("HOME not set\n", 2), NULL);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = my_getenv("OLDPWD", envp);
		if (!path || path[0] == '\0')
		{
			ft_putstr_fd("OLDPWD not set\n", 2);
			return (NULL);
		}
		ft_putendl_fd(path, 1);
	}
	else
		path = args[1];
	return (path);
}
