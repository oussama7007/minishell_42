/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:14:22 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/10 03:03:44 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcount(const char *str, char delim)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == delim || *str == '\t')
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*ft_worddup(const char *start, const char *end)
{
	size_t	len;
	char	*word;
	size_t	i;

	len = end - start;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	ft_free_split(char **result, int index)
{
	while (index > 0)
		free(result[--index]);
	free(result);
}

static int	ft_fill_result(const char *s, char c, char **result)
{
	int			i;
	const char	*start;

	i = 0;
	while (*s)
	{
		while (*s == c || *s == '\t')
			s++;
		if (*s)
		{
			start = s;
			while (*s && *s != c && *s != '\t')
				s++;
			result[i] = ft_worddup(start, s);
			if (!result[i])
			{
				ft_free_split(result, i);
				return (0);
			}
			i++;
		}
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = ft_wordcount(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	if (!ft_fill_result(s, c, result))
		return (NULL);
	return (result);
}
