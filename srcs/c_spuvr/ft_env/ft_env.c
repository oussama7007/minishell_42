/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:33:39 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/18 16:48:54 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

int ft_env(char **args, char ***env_ptr)
{
    int i;
    
    if (!env_ptr || !(*env_ptr))
        return (1); // Environment pointer invalid
    
    // Simple iteration - no sorting, no fancy formatting
    i = 0;
    while ((*env_ptr)[i])
    {
        // Only print entries containing '=' (actual environment variables)
        if (ft_strchr((*env_ptr)[i], '='))
            ft_putendl_fd((*env_ptr)[i], STDOUT_FILENO);
        i++;
    }
    
    return (0); // Success
}
