/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:13:30 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/21 11:49:26 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
char *ft_strjoin_free(char *s1, char *s2)
{
    char *result = ft_strjoin(s1, s2);
    free(s1);
    return result;
}
char *qestion_mark(int ex_status)
{
    return ft_itoa(ex_status);
}
int get_quotes_type(char quote_type)
{
    return (quote_type == '"') ? 2 : 1;
}