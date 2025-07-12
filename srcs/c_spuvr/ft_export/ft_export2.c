/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:37:18 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/12 15:13:33 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

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
