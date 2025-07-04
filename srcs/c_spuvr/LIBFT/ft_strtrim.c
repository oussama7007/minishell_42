/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:52:38 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/04 17:46:47 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char *set)
{
	size_t	st;
	size_t	end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	st = 0;
	while (s1[st] != '\0' && ft_strchr(set, s1[st]))
		st++;
	end = ft_strlen(s1);
	while (end > st && ft_strchr(set, s1[end - 1]))
		end--;
	str = malloc(end - st + 1);
	if (!str)
		return (0);
	ft_strlcpy(str, &s1[st], end - st + 1);
	return (str);
}
