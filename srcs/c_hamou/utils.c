/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:13:30 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/16 14:13:34 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
// char *ft_strdup(const char *s1)
// {
//     int i = 0;
//     char *copy;

//     while (s1[i])
//         i++;

//     copy = (char *)malloc(sizeof(char) * (i + 1));
//     if (!copy)
//         return NULL;

//     i = 0;
//     while (s1[i])
//     {
//         copy[i] = s1[i];
//         i++;
//     }
//     copy[i] = '\0';

//     return copy;
// }
// int ft_strlen(char *line)
// {
//     int i;

//     i = 0;
//     while(line[i])
//         i++;
//     return i;
// }
// int is_space(int  c)
// {
//     return(c >= 9 && c <= 32);
// }
// size_t ft_strlcpy(char *dst, char *src, size_t dstsize)
// {
//     size_t i = 0;

//     if (dstsize == 0)
//         return (ft_strlen(src));
//     while (i < dstsize - 1 && src[i])
//     {
//         dst[i] = src[i];
//         i++;
//     }
//     dst[i] = '\0';
//     return (ft_strlen(src));
// }
// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while ((i < n) && (s1[i] || s2[i]))
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	return (0);
// }