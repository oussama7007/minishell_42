/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:18:20 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/06 18:42:23 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H
# include <unistd.h>
# include <stdlib.h>
# include "built_functions.h"
# include "LIBFT/libft.h"


char	*ft_strdup(char *s);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_arrlen(char **arr);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif