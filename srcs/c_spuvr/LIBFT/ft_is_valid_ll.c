/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_ll.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:22:27 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/10 22:39:47 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	check_overflow(unsigned long long res, int digit, int sign)
{
	unsigned long long	cutoff;
	int					cutlim;

	if (sign == 1)
	{
		cutoff = LLONG_MAX / 10;
		cutlim = LLONG_MAX % 10;
		if (res > cutoff || (res == cutoff && digit > cutlim))
			return (0);
	}
	else
	{
		cutoff = -(unsigned long long)LLONG_MIN / 10;
		cutlim = -(unsigned long long)LLONG_MIN % 10;
		if (res > cutoff || (res == cutoff && digit > cutlim))
			return (0);
	}
	return (1);
}

static void	zft_initialize(int *i, int *s, long long *r)
{
	*i = 0;
	*s = 1;
	*r = 0;
}

int	is_valid_long_long(const char *str)
{
	int			i;
	long long	result;
	int			sign;

	zft_initialize(&i, &sign, &result);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		sign = 1;
		if (!check_overflow(result, str[i] - '0', sign))
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign && str[i] == '\0');
}
