/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:20:52 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/30 09:24:12 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "header.h"
static char *get_var_value(char *new_word, char **envp)
{
    int var_len;

    var_len = ft_strlen(new_word);
    while(*envp)
    {
        if(ft_strncmp(*envp, new_word, var_len) == 0 && (*envp)[var_len] == '=')
                return(*envp + var_len + 1);
        envp++;
    }
    return NULL;
}
static char *expand_value_func(char *value, char **envp)
{
    int i = 0;
    int j = 0;
    char *new_word = NULL;
    char *var_value = NULL;
    char *result = NULL;
    char *tmp = NULL;
    char chr_str[2];
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
            while((value[j] && ft_isalnum(value[j])) || value[j] == '_')
                j++;
            new_word = ft_substr(value, i, j - i);
            // condition if fail malloc;
            var_value = get_var_value(new_word, envp);
            if(!var_value)
                return NULL;
            free(new_word);
            result = ft_strjoin(result, var_value);
            // condition if fail
            j += ft_strlen(var_value); 
        }
        else 
        {
            chr_str[0] = value[i];
            chr_str[1] = '\0';
            result = ft_strjoin(result, chr_str);
            i++;   
        }
    }
    return result;
}
t_token *expand(t_token **tokens,char **env)
{
   t_token *tmp = *tokens;
   char *expand_value;

   while(tmp)
   {
        if(ft_strchr(tmp->value, '$') && tmp->quotes_type != 1)
        {
            expand_value = expand_value_func(tmp->value, env);
            if(expand_value)
            {
                free(tmp->value);
                tmp->value = expand_value;
            }
        }
        tmp = tmp->next;
   }
   return *tokens;
}