/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:37:57 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/18 09:07:42 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static int	get_length(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*negative(int len, char *str, unsigned int num)
{
	while (len > 0)
	{
		str[len--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

static char	*positive(int len, char *str, unsigned int num)
{
	while (len >= 0)
	{
		str[len--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

static	char	*alloc(int len)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	num;
	char			*tmp;

	len = get_length(n);
	str = alloc(len);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	else
		num = n;
	if (n < 0)
		tmp = negative(len, str, num);
	else
		tmp = positive(len, str, num);
	return (tmp);
}
