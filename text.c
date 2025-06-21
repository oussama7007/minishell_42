#include "header.h"
#include "header.h"
          
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:12:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/21 11:03:20 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char *handle_quoted_part(char **start, int *quotes_type, char **env, int ex_status)
{
    char quote_type = **start;
    char *end = *start + 1;
    char *accumulator = ft_strdup("");
    int local_quotes_type;
    int *target_quotes_type = quotes_type ? quotes_type : &local_quotes_type;

    *target_quotes_type = get_quotes_type(quote_type);
    
    if (quote_type == '\'')
    {
        free(accumulator);
        return singel_quotes_handler(start);
    }
    
    // Rest of double quotes processing remains the same
    // ...
}char *handle_quoted_part(char **start, int *quotes_type, char **env, int ex_status)
{
    char quote_type = **start;
    char *end = *start + 1;
    char *accumulator = ft_strdup("");
    char *tmp;
    int local_quotes_type;
    int *target_quotes_type = quotes_type ? quotes_type : &local_quotes_type;
    
    // Set quotes type for both single and double quotes
    *target_quotes_type = get_quotes_type(quote_type);
    
    if (quote_type == '\'')
    {
        free(accumulator);
        return singel_quotes_handler(start);
    }
    
    // Rest of the function remains the same
    // ...
}