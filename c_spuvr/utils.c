/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:08:03 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/05 18:21:16 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h"

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\0')
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*d;

	i = 0;
	if (s[i] == NULL)
		return (NULL);
	d = malloc(sizeof(char) * ft_strlen(s) + 1);
	while (s[i])
	{
		d[i] = s[i]
		i++;
	}
	d[i] = '\0';
	return (d);
}
