/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:20:52 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/15 17:12:37 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "header.h"
char *get_var_value(char *new_word, char **envp)
{
    int var_len;

    var_len = ft_strlen(new_word);
    while(*envp)
    {
        if(ft_strncmp(*envp, new_word, var_len) == 0 && (*envp)[var_len] == '=')
                return(*envp + var_len + 1);
        envp++;
    }
    return ft_strdup("");
}
char *expand_value_func(char *str, char **envp)
{
    char *result = NULL;
    int i = 0;

    while (str[i]) {
        if (str[i] == '$') {
            i++;
            int j = i;
            while (str[j] && (ft_isalnum(str[j]) || str[j] == '_')) j++;
            char *var_name = ft_substr(str, i, j - i);
            char *var_value = get_var_value(var_name, envp);
            result = ft_strjoin(result, var_value);
            free(var_name);
            i = j;
        } else {
            char chr[2] = {str[i], 0};
            result = ft_strjoin(result, chr);
            i++;
        }
    }
    return result;
}
