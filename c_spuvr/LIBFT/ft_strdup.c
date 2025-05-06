/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:17:41 by oadouz            #+#    #+#             */
/*   Updated: 2024/11/15 23:29:41 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s1);
	dup = malloc(len + 1 * (sizeof(char)));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, len + 1);
	return (dup);
}
