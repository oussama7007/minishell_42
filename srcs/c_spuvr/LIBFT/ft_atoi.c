/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:47:45 by oadouz            #+#    #+#             */
/*   Updated: 2024/11/17 00:07:37 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_initialize(int *i, int *s, unsigned long long *r)
{
	*i = 0;
	*s = 1;
	*r = 0;
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	r;
	int					s;

	ft_initialize(&i, &s, &r);
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		if (r > 9223372036854775807 && s == -1)
			return (0);
		if (r > 9223372036854775807 && s == 1)
			return (-1);
		i++;
	}
	return (r * s);
}
