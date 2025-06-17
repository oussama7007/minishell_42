/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:12:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/17 10:48:30 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
static t_token *handle_operator(char **start, int quotes_type)
{
    char *word;
    t_token *token;
    char *end = *start;

    if (*end == '<' && *(end + 1) == '<')
        end += 2;
    else if (*end == '>' && *(end + 1) == '>')
        end += 2;
    else
        end++;
    word = ft_strndup(*start, end - *start);
    if (!word)
        return (NULL);
    token = new_token(get_token_type(word), word, quotes_type);
    free(word);
    *start = end;
    return (token);
}
static char *handle_quoted_part(char **start, int *quotes_type, char **envp)
{
    char quote_type = **start;
    char *end;
    char *accumulator = NULL;
    char *tmp;
    char *var_name;
    char *var_value;
    char chr_str[2] = {0, 0};

    if (quote_type == '"')
        *quotes_type = 2;
    else
        *quotes_type = 1;
    
    (*start)++;
    end = *start;
    if (quote_type == '\'')
    {
        while (*end && *end != quote_type) end++;
        accumulator = ft_strndup(*start, end - *start);
    }
    else // Double quotes
    {
        while (*end && *end != quote_type)
        {
            if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '_' || *(end + 1) == '?'))
            {
                end++;
                char *var_start = end;
                while (*end && *end != quote_type && (ft_isalnum(*end) || *end == '_' || *end == '?'))
                    end++;
                var_name = ft_strndup(var_start, end - var_start);
                var_value = get_var_value(var_name, envp);
                tmp = accumulator;
                accumulator = ft_strjoin(tmp, var_value);
                free(tmp);
                free(var_name);
                if (var_value != get_var_value(var_name, envp))
                    free(var_value);
            }
            else
            {
                chr_str[0] = *end;
                tmp = accumulator;
                accumulator = ft_strjoin(tmp, chr_str);
                free(tmp);
                end++;
            }
        }
    }
    if (*end != quote_type)
    {
        free(accumulator);
        return NULL;
    }
    *start = end + 1;
    if (!accumulator)
        accumulator = ft_strdup("");
    return accumulator;
}

static char *handle_unquoted_part(char **start, int *quotes_type, char **envp)
{
    char *accumulator = NULL;
    char *tmp;
    char *var_name;
    char *var_value;
    char chr_str[2] = {0, 0};
    char *end = *start;

    *quotes_type = 0;

    while (*end && *end != ' ' && *end != '\t' && *end != '|' &&
           *end != '<' && *end != '>' && *end != '\'' && *end != '"')
    {
        if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '_' || *(end + 1) == '?' || *(end + 1) == '"'))
        {
            
            end++;
            if (*end == '"') // Handle $"string"
            {
                end++; // Skip the opening "
                char *quote_start = end;
                while (*end && *end != '"') end++;
                if (*end == '"')
                {
                    char *quoted = ft_strndup(quote_start, end - quote_start);
                    char *expanded = expand_value_func(quoted, envp);
                    tmp = accumulator;
                    accumulator = ft_strjoin(tmp, expanded);
                    free(tmp);
                    free(quoted);
                    free(expanded);
                    end++; // Skip the closing "
                }
                else
                {
                    free(accumulator);
                    return NULL;
                }
            }
            else // Handle regular $VARIABLE
            {
            
                char *var_start = end;
                while (*end && (ft_isalnum(*end) || *end == '_' || *end == '?') &&
                       *end != ' ' && *end != '\t' && *end != '|' &&
                       *end != '<' && *end != '>' && *end != '\'' && *end != '"')
                    end++;
                var_name = ft_strndup(var_start, end - var_start);
                var_value = get_var_value(var_name, envp);
                tmp = accumulator;
                accumulator = ft_strjoin(tmp, var_value);
                free(tmp);
                free(var_name);
                //if (var_value != get_var_value(var_name, envp)) // Free only if allocated
                    //free(var_value);
            }
        }
        else
        {
            chr_str[0] = *end;
            tmp = accumulator;
            accumulator = ft_strjoin(tmp, chr_str);
            free(tmp);
            end++;
        }
    }
    *start = end;
    if (!accumulator)
        accumulator = ft_strdup("");
   
    return accumulator;
}

static t_token *handle_word(char **start, int *quotes_type , char **my_env)
{
    char *accumulator = NULL;
    char *segment;
    char *tmp;
    t_token *token = NULL;
    char *expanded_value;
    while (**start && **start != ' ' && **start != '\t'
        && **start != '|' && **start != '<' && **start != '>')
    {
        if (**start == '\'' || **start == '"')
            segment = handle_quoted_part(start, quotes_type, my_env);
        else
            segment = handle_unquoted_part(start, quotes_type, my_env);
        if (!segment)
        {
            
            return (free(accumulator), NULL);
        }
        tmp = accumulator;
        accumulator = ft_strjoin(tmp, segment);
        free(tmp);
        free(segment);
        if (!accumulator)
        {
            
            return (NULL);
        }    
    }
    if(accumulator)
    {
        
        token = new_token(get_token_type(accumulator), accumulator, *quotes_type);
        free(accumulator);
        return (token);
    }
    free(accumulator);
    return (NULL);
}
t_token     *tokenize(char *line, char **my_env)
{
    t_token *tokens = NULL;
    char *start = line;
    t_token *token;
    int quotes_type = 0;

    while (*start)
    {
        while (*start && (*start == ' ' || *start == '\t'))
            start++;
        // if (!*start)
        //     break;
        if (*start == '|' || *start == '<' || *start == '>')
        {
            token = handle_operator(&start, quotes_type);
            if (!token)
                return (free_tokens(tokens), NULL);
            add_token(&tokens, token);
        }
        else if(*start) // Check if there's still input to process
        {
            token = handle_word(&start, &quotes_type, my_env);
            if (!token)
                return (free_tokens(tokens), NULL);
            if(token)// check it 
                add_token(&tokens, token);
        }
    }
    return (tokens);
}
t_token     *new_token(int type, char *word, int quotes_type)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if(!new)
        return (NULL);
    new->value = ft_strdup(word);
    if(!new->value)
        return (free(new), NULL); // test this line 
    new->type = type;
    new->quotes_type = quotes_type;
    new->next = NULL;
    return new;
}
int     get_token_type(char *line)
{
    if(!line && !line[0])
        return(TOKEN_WORD);
    if(line[0] == '|')
        return (TOKEN_PIPE);
    if(line[0] == '<' && line[1] == '<')
        return (TOKEN_RED_HEREDOC);
    if(line[0] == '>' && line[1] == '>')
        return (TOKEN_RED_APPEND);
    if(line[0] == '<')
        return (TOKEN_RED_IN);
    if(line[0] == '>')
        return (TOKEN_RED_OUT);
    return(TOKEN_WORD);
}
void    add_token(t_token **tokens, t_token *token)
{
    t_token *tmp =  NULL;
    if(!*tokens)
        *tokens = token;
    else 
    {
        tmp = *tokens;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = token;
    }
}