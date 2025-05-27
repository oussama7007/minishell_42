/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:20:52 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/27 16:55:01 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "header.h"
static char *get_var_value(char *new_word, char **envp)
{
    int var_len;

    var_len = ft_strlen(new_word);
    while(*envp)
    {
        if(ft_strncmp(*envp, new_word, var_len) == 0 && *envp[var_len] == '=')
            return(**(envp + var_len + 1));
        *(envp++);
    }
}
static char *expand_value(char *value, char **envp)
{
    int i = 0;
    int j = 0;
    char *new_word = NULL
    char *var_value = NULL;
    char *result = NULL;
    while(value[i])
    {
        if(value[i] == '$')
        {
            i++;
            if(value[i] == '?')
            {
                // tanchouf kifach ndir liha;
                continue;
                i++;
            }
            j = i;
            while((value[j] && ft_isalnum(value[i])) || value[j] == '_')
                j++;
            new_word = ft_strndup(value, j - i);
            // condition if fail malloc;
            var_value = get_var_value(new_word, envp);
            free(new_word);
            result = ft_strjoin(result, var_value);
            // condition if fail
            j += ft_strlen(var_value); 
        }
        else 
            result = 
        i++;
    }
}
t_token *expand(t_token **tokens,char **env)
{
   t_token *tmp = *tokens;
   char *expand_value;

   while(tmp)
   {
        if(ft_strchr(tmp->value, '$'))
        {
            expand_value = expand_value(tmp->value, env);
            if(expand_value)
            {
                free(tmp->value)
                tmp->value = expand_value;
            }
        }
        tmp = tmp->next;
   }
}