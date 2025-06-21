/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:12:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/21 15:27:08 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


static char *Handle_regular_accumualtor(char *var_start, char *end, char **env, char *accumulator)
{
    char *var_name;
    char *var_value;
    char *value_to_use;
    char *tmp;

    var_name = ft_strndup(var_start, end - var_start);
    var_value = get_var_value(var_name, env);
    free(var_name);
    
    value_to_use = var_value ? ft_strdup(var_value) : ft_strdup("");
    
    if (accumulator)
    {
        tmp = accumulator;
        accumulator = ft_strjoin(tmp, value_to_use);
        free(tmp);
        free(value_to_use);
    }
    else
        accumulator = value_to_use;
    
    return accumulator;
}

static char *singel_quotes_handler(char **input_start)
{
    char *start = *input_start + 1;
    char *end = start;
    char *accumulator;
    while (*end && *end != '\'')
        end++;
    if (*end != '\'')
        return NULL; 
    accumulator = ft_strndup(start, end - start);
    *input_start = end + 1;
    return accumulator;
}

char *handle_quoted_part(char **start, int *quotes_type, char **env, int ex_status)
{
    char quote_type = **start;
    char *end = *start + 1;
    char *accumulator = ft_strdup("");
    char *tmp;
    int local_quotes_type;
    int *target_quotes_type = quotes_type ? quotes_type : &local_quotes_type;
    
    *target_quotes_type = get_quotes_type(quote_type);
     
    if (quote_type == '\'')
    {
        free(accumulator);  // Free the initial empty string
        accumulator = singel_quotes_handler(start);
        return accumulator;
    }
    
    // Double quotes
    while (*end && *end != '"')
    {
        if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '_' || *(end + 1) == '?'))
        {
            end++;
            if (*end == '?')
            {
                tmp = qestion_mark(ex_status);
                char *new_accumulator = ft_strjoin(accumulator, tmp);
                free(accumulator);
                free(tmp);
                accumulator = new_accumulator;
                end++;
            }
            else
            {
                char *var_start = end;
                while (*end && *end != '"' && (ft_isalnum(*end) || *end == '_' || *end == '?'))
                    end++;
                accumulator = Handle_regular_accumualtor(var_start, end, env, accumulator);
            }
        }
        else
        {
            char ch = *end;
            tmp = ft_strndup(&ch, 1);
            char *new_accumulator = ft_strjoin(accumulator, tmp);
            free(accumulator);
            free(tmp);
            accumulator = new_accumulator;
            end++;
        }
    }
    
    if (*end != '"')
    {
        free(accumulator);
        return NULL;
    }
    *start = end + 1;
    return accumulator;
}

static char *handle_double_quote_dollar(char **end, char *accumulator, char **env, int ex_status)
{
 
    int dummy_quotes_type;
    char *quoted_value;
    
    quoted_value = handle_quoted_part(end, &dummy_quotes_type, env, ex_status);
    if (!quoted_value)
        return NULL;

    if (accumulator)
    {
        char *tmp = accumulator;
        accumulator = ft_strjoin(tmp, quoted_value);
        free(tmp);
        free(quoted_value);
    }
    else
        accumulator = quoted_value;
    
    return accumulator;
}

static char *handle_question_mark(char **end, int ex_status, char *accumulator)
{
    char *status_str = qestion_mark(ex_status);
    
    if (accumulator)
    {
        char *tmp = accumulator;
        accumulator = ft_strjoin(tmp, status_str);
        free(tmp);
        free(status_str);
    }
    else
        accumulator = status_str;
    (*end)++;
    return accumulator;
}

static char *handle_regular_dollar(char **end, char **env, int ex_status, char *accumulator)
{
    char *var_start = *end;
    
    while (**end && (ft_isalnum(**end) || **end == '_' || **end == '?') && \
            **end != ' ' && **end != '\t' && **end != '|' && \
            **end != '<' && **end != '>' && **end != '\'' && **end != '"')
        (*end)++;
    return Handle_regular_accumualtor(var_start, *end, env, accumulator);
}

static char *handle_dollar_case(char **end, char **env, int ex_status, char *accumulator)
{   
    (*end)++;
    if (**end == '?')
        return handle_question_mark(end, ex_status, accumulator);
    else if (**end == '"')
        return handle_double_quote_dollar(end, accumulator, env, ex_status);
    else
        return handle_regular_dollar(end, env, ex_status, accumulator);
}

static char *handle_normal_char(char **end_ptr, char *accumulator)
{
    char ch = **end_ptr;
    char *tmp = ft_strndup(&ch, 1);
    
    if (accumulator)
    {
        char *new_accumulator = ft_strjoin(accumulator, tmp);
        free(accumulator);
        free(tmp);
        accumulator = new_accumulator;
    }
    else
        accumulator = tmp;
    (*end_ptr)++;
    return accumulator;
}

char *handle_unquoted_part(char **start, int *quotes_type, char **env, int ex_status)
{
    char *end = *start;
    char *accumulator = NULL;
    *quotes_type = 0;

    while (*end && *end != ' ' && *end != '\t' && *end != '|' &&
           *end != '<' && *end != '>' && *end != '\'' && *end != '"')
    {
        if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '_' || *(end + 1) == '?' || *(end + 1) == '"'))
            accumulator = handle_dollar_case(&end, env, ex_status, accumulator);
        else
            accumulator = handle_normal_char(&end, accumulator);
    }
    *start = end;
    return accumulator ? accumulator : ft_strdup("");
}

static t_token *handle_word(char **start, int *quotes_type, char **my_env, int ex_status)
{
    char *accumulator = NULL;
    char *segment;
    char *tmp;

    while (**start && **start != ' ' && **start != '\t'
        && **start != '|' && **start != '<' && **start != '>')
    {
        segment = process_segment(start, quotes_type, my_env, ex_status);
        if (!segment)
        {
            free(accumulator);
            return NULL;
        }
        
        if (accumulator)
        {
            tmp = accumulator;
            accumulator = ft_strjoin(tmp, segment);
            free(tmp);
            free(segment);
        }
        else
            accumulator = segment;
    }
    
    if (!accumulator)
        accumulator = ft_strdup("");
    
    return new_token(get_token_type(accumulator), accumulator, *quotes_type);
}

t_token *tokenize(char *line, char **my_env, int ex_status)
{
    t_token *tokens = NULL;
    char *start = line;
    int quotes_type = 0;

    while (*start)
    {
        while (*start == ' ' || *start == '\t')
            start++;
        if (!*start)
            break;
            
        if (*start == '|' || *start == '<' || *start == '>')
        {
            t_token *token = handle_operator(&start, quotes_type);
            if (!token)
                return free_tokens(tokens), NULL;// need to look about it
            add_token(&tokens, token);
        }
        else
        {
            t_token *token = handle_word(&start, &quotes_type, my_env, ex_status);
            if (!token)
                return free_tokens(tokens), NULL;
            add_token(&tokens, token);
        }
    }
    return tokens;
}





































// // look at deep seek has your last issue you faced 