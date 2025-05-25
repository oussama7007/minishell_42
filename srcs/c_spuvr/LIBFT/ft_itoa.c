/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:37:57 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/24 14:36:18 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	ft_fillstr(char *str, int n, int len)
{
	if (n == 0)
		str[0] = '0';
	str[len] = '\0';
	while (n != 0)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
}

char	*ft_itoa(t_head_list *head, int n)
{
	int		len;
	char	*str;
	int		is_negative;

	if (n == -2147483648)
		return (ft_strdup(head, "-2147483648"));
	is_negative = (n < 0);
	len = ft_count_digits(n) + is_negative;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (is_negative)
	{
		str[0] = '-';
		n = -n;
	}
	ft_fillstr(str + is_negative, n, len - is_negative);
	return (str);
}
