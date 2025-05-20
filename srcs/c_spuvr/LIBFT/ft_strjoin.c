/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:41:29 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/20 17:09:07 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strjoin_length(char const *s1, char const *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	if (s1)
		len_s1 = ft_strlen(s1);
	if (s2)
		len_s2 = ft_strlen(s2);
	return (len_s1 + len_s2);
}

static void	ft_strjoin_concat(char *new, char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			new[i] = s1[i];
			i++;
		}
	}
	j = 0;
	if (s2)
	{
		while (s2[j])
		{
			new[i] = s2[j];
			i++;
			j++;
		}
	}
	new[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		total_len;

	total_len = ft_strjoin_length(s1, s2);
	new = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!new)
		return (NULL);
	ft_strjoin_concat(new, s1, s2);
	return (new);
}
