/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:16:02 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/12 03:08:15 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
char *ft_strndup( char *s, size_t n)
{
    char *dup;
    size_t len;

    len = ft_strlen(s);
    if (len > n)
        len = n;
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    ft_strlcpy(dup, s, len + 1);
    return (dup);
}