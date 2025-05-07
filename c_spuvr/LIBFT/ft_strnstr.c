/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:15:06 by oadouz            #+#    #+#             */
/*   Updated: 2024/11/15 18:25:17 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n_len;

	if (!haystack && len == 0)
		return (NULL);
	n_len = ft_strlen(needle);
	if (n_len == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i + n_len <= len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && j < n_len)
		{
			j++;
		}
		if (j == n_len)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
