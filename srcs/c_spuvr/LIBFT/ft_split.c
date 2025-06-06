/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:28:04 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/25 19:20:21 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

static size_t	ft_count_wd(const char *s, char c)
{
	size_t	wd;
	int		flag;

	wd = 0;
	flag = 1;
	while (*s)
	{
		if (*s == c)
			flag = 1;
		else
		{
			if (flag)
			{
				wd++;
				flag = 0;
			}
		}
		s++;
	}
	return (wd);
}

static int	ft_pick_place(char **arr, int pos, size_t buffer)
{
	int	i;

	i = 0;
	arr[pos] = malloc(buffer);
	if (arr[pos] == NULL)
	{
		while (i < pos)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		return (1);
	}
	return (0);
}

static int	ft_fill_strs(char **arr, const char *s, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			if (ft_pick_place(arr, i, len + 1))
				return (1);
			ft_strlcpy(arr[i], s - len, len + 1);
			i++;
		}
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	size_t	word_count;
	char	**arr;

	if (s == NULL)
		return (NULL);
	word_count = ft_count_wd(s, c);
	arr = malloc((word_count + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr[word_count] = NULL;
	if (ft_fill_strs(arr, s, c))
		return (NULL);
	return (arr);
}

// #include "libft.h"

// static size_t	ft_count_wd(const char *s, char c)
// {
// 	size_t	wd;
// 	int		flag;

// 	wd = 0;
// 	flag = 1;
// 	while (*s)
// 	{
// 		if (*s == c)
// 			flag = 1;
// 		else
// 		{
// 			if (flag)
// 			{
// 				wd++;
// 				flag = 0;
// 			}
// 		}
// 		s++;
// 	}
// 	return (wd);
// }


// static int	ft_pick_place(t_head_list *head, char **arr, int pos, size_t buffer)
// {
// 	int	i;

// 	i = 0;
// 	arr[pos] = gc_malloc(head,buffer);
// 	if (arr[pos] == NULL)
// 	{
// 		// while (i < pos)
// 		// {
// 		// 	free(arr[i]);
// 		// 	i++;
// 		// }
// 		// free(arr);
// 		free_gc(head);
// 		return (1);
// 	}
// 	return (0);
// }

// static int	ft_fill_strs(t_head_list *head, char **arr, const char *s, char c)
// {
// 	size_t	len;
// 	size_t	i;

// 	i = 0;
// 	while (*s)
// 	{
// 		len = 0;
// 		while (*s == c && *s)
// 			s++;
// 		while (*s != c && *s)
// 		{
// 			len++;
// 			s++;
// 		}
// 		if (len > 0)
// 		{
// 			if (ft_pick_place(head, arr, i, len + 1))
// 				return (1);
// 			ft_strlcpy(arr[i], s - len, len + 1);
// 			i++;
// 		}
// 	}
// 	return (0);
// }

// char	**ft_split(t_head_list *head,const char *s, char c)
// {
// 	size_t	word_count;
// 	char	**arr;

// 	if (s == NULL)
// 		return (NULL);
// 	word_count = ft_count_wd(s, c);
// 	arr = gc_malloc(head ,(word_count + 1) * sizeof(char *));
// 	if (arr == NULL)
// 		return (NULL);
// 	arr[word_count] = NULL;
// 	if (ft_fill_strs(head, arr, s, c))
// 		return (NULL);
// 	return (arr);
// }
