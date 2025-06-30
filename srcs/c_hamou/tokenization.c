/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:12:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/29 23:41:12 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
static char	*join_and_free(char *acc, char *to_add)
{
	char	*new;

	new = ft_strjoin(acc, to_add);
	free(acc);
	free(to_add);
	return (new);
}
char *Handle_regular_accumualtor(char *var_start, char *end, char **env, char *accumulator)
{
    char		*var_name;
    char		*var_value;
    const char	*value_to_join;
    char		*tmp;

    var_name = ft_strndup(var_start, end - var_start);
    var_value = get_var_value(var_name, env);
    free(var_name);
    value_to_join = var_value;
    if (!value_to_join)
        value_to_join = "";
    if (accumulator)
    {
        tmp = accumulator;
        accumulator = ft_strjoin(tmp, value_to_join);
        free(tmp);
    }
    else
        accumulator = ft_strdup(value_to_join);
    return (accumulator);
}

static char *singel_quotes_handler(char **input_start, t_data *data)
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
    if(!data->delimiter)
        data->delimiter = 0;
    return accumulator;
}

char *handle_quoted_part(char **start, char **env, t_data *data)
{
    char quote_type ;
    char *end = *start + 1;
    char *accumulator;
    char *tmp;

    
    quote_type = **start;
    accumulator = ft_strdup("");
    if (quote_type == '\'')
    {
            free(accumulator);
            accumulator = singel_quotes_handler(start, data);
            return accumulator;
    }
    // Double quotes
     while (*end && *end != '"')
    {
        if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '?') && !data->delimiter)
        {
            end++;
            if (*end == '?')
            {
                tmp = qestion_mark(data->ex_status);
                char *new_accumulator = ft_strjoin(accumulator, tmp);
                free(accumulator);
                free(tmp);
                accumulator = new_accumulator;
                end++;
            }
            else
            {
                char *var_start = end;
                while (*end && *end != '"' && (ft_isalnum(*end) || *end == '?'))
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
        return(free(accumulator) ,NULL);
    *start = end + 1;
    return accumulator;
}

static char *handle_double_quote_dollar(char **end, char *accumulator, char **env, t_data *data)
{
 
    // int dummy_quotes_type;
    char *quoted_value;
    
    quoted_value = handle_quoted_part(end, env, data );
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

static char *handle_question_mark(char **end, char *accumulator, t_data *data)
{
    char *status_str = qestion_mark(data->ex_status);
    
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

static char *handle_regular_dollar(char **end, char **env, t_data *data, char *accumulator)
{
    char *var_start = *end;
    
    while(**end && (ft_isalnum(**end) || **end == '?') && !is_space(**end) && !is_operator(**end) && !is_quotes(**end))
        (*end)++;
    return Handle_regular_accumualtor(var_start, *end, env, accumulator);
}

char *handle_dollar_case(char **end, char **env, char *accumulator, t_data *data)
{   
    (*end)++;
    if (**end == '?')
        return handle_question_mark(end, accumulator, data);
    else if (**end == '"')
        return handle_double_quote_dollar(end, accumulator, env, data);
    else
            return handle_regular_dollar(end, env, data, accumulator);
        
}

char *handle_normal_char(char **end_ptr, char *accumulator, t_data *data)
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
    data->delimiter = 0;
    return accumulator;
}

char *handle_unquoted_part(char **start, char **env, t_data *data)
{
    char *end = *start;
    char *accumulator = NULL;
    data->quote_type = 0;


    while(*end && !is_space(*end) && !is_operator(*end) && !is_quotes(*end))
    {
        if (*end == '$' && (ft_isalpha(*(end + 1))  || *(end + 1) == '?' || *(end + 1) == '"') && !data->delimiter)
                accumulator = handle_dollar_case(&end, env, accumulator, data);
        else
            accumulator = handle_normal_char(&end, accumulator, data);
    }
    *start = end;
    if(!accumulator)
        return ft_strdup("");
    return accumulator;
}


t_token *handle_word(char **start,char **my_env, t_data *data)
{
    char	*accumulator;
    char	*segment;
    char	*tmp;
    t_token	*token;

    accumulator = NULL;
    while (**start && !is_space(**start) && !is_operator(**start))
    {
        segment = process_segment(start, my_env, data);
        if (!segment)
            return (free(accumulator),NULL);
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
    token = new_token(get_token_type(accumulator), accumulator, data->quote_type);
    return (free(accumulator),token);
}
t_token *tokenize(char *line, char **my_env, t_data *data)
{
    t_token *tokens = NULL;
    char *start = line;
    // int quotes_type = 0;
    // t_delimiter del;

    
    while (*start)
    {
        while (is_space(*start))
            start++;
        if (!*start)
            break;
            
        if (is_operator(*start))
        {
            t_token *token = handle_operator(&start, data);
            if (!token)
                return free_tokens(tokens), NULL;// need to look about it
            add_token(&tokens, token);
        }
        else
        {
            t_token *token = handle_word(&start, my_env, data);
            if (!token)
                return free_tokens(tokens), NULL;
            add_token(&tokens, token);
        }
    }
    return tokens;
}



// // 