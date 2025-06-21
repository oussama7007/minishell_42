/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:41:41 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/21 17:30:43 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_calloc(1, sizeof(char)));
	if (s_len - start < len)
		len = s_len - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// #include "libft.h"

// char	*ft_substr(t_head_list *head, char const *s, unsigned int start, size_t len)
// {
// 	size_t	s_len;
// 	char	*str;

// 	if (!s)
// 		return (0);
// 	s_len = ft_strlen(s);
// 	if (start >= s_len)
// 	{
// 		str = gc_malloc(head,1);
// 		if (!str)
// 			return (0);
// 		str[0] = '\0';
// 		return (str);
// 	}
// 	if (len > s_len - start)
// 		len = s_len - start;
// 	str = gc_malloc(head,len + 1);
// 	if (!str)
// 		return (0);
// 	ft_strlcpy(str, s + start, len + 1);
// 	return (str);
// }
