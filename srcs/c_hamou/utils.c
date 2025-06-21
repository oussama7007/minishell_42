/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:13:30 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/21 16:32:58 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char *qestion_mark(int ex_status)
{
    return ft_itoa(ex_status);
}
int get_quotes_type(char quote_type)
{
    if(quote_type == '"')
        return 2;
    return 1; 
}
int     is_space(char c)
{
    return (c == ' ' || c =='\t');
}
int     is_operator(char c)
{
    return(c == '<' || c == '>' || c == '|');
}
int     is_quotes(char c)
{
    return(c == '"' || c == '\'');
}