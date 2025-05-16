/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:42:30 by oadouz            #+#    #+#             */
/*   Updated: 2024/11/17 04:12:42 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ar;
	size_t	len;

	if (size && (count * size) / size != count)
		return (NULL);
	len = count * size;
	ar = malloc(len);
	if (!ar)
		return (NULL);
	ft_bzero(ar, len);
	return (ar);
}
