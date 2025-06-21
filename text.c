/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                               :::      +:+
/*   Created: 2025/05/12 02:12:47 by oait-si-          ###   ###   ###       */
/*   Updated: 2025/06/21 14:15:14 by oait-si-         ###   ###   ###       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Handles the accumulation of environment variable values
static char *Handle_regular_accumualtor(char *var_start, char *end, char **env, char *accumulator)
{
    char *var_name;
    char *var_value;
    char *value_to_use;
    char *tmp;

    // Duplicate the variable name from var_start to end
    var_name = ft_strndup(var_start, end - var_start);
    // Get the value of the variable from the environment
    var_value = get_var_value(var_name, env);
    free(var_name);
    
    // If the variable exists, use its value; otherwise, use an empty string
    value_to_use = var_value ? ft_strdup(var_value) : ft_strdup("");
    
    if (accumulator)
    {
        // Join the accumulator with the value_to_use
        tmp = accumulator;
        accumulator = ft_strjoin(tmp, value_to_use);
        free(tmp);
        free(value_to_use);
    }
    else
        accumulator = value_to_use;
    
    return accumulator;
}

// Handles single-quoted strings by extracting the content between single quotes
static char *singel_quotes_handler(char **input_start)
{
    char *start = *input_start + 1; // Skip the opening single quote
    char *end = start;
    char *accumulator;

    // Find the closing single quote
    while (*end && *end != '\'')
        end++;
    if (*end != '\'') // Unclosed single quote
        return NULL; 
    // Duplicate the string between start and end
    accumulator = ft_strndup(start, end - start);
    *input_start = end + 1; // Move past the closing single quote
    return accumulator;
}

// Handles quoted parts (single or double quotes)
char *handle_quoted_part(char **start, int *quotes_type, char **env, int ex_status)
{
    char quote_type = **start;
    char *end = *start + 1;
    char *accumulator = ft_strdup("");
    char *tmp;
    int local_quotes_type;
    int *target_quotes_type = quotes_type ? quotes_type : &local_quotes_type;
    
    // Set the quotes_type based on the quote character
    *target_quotes_type = get_quotes_type(quote_type);
     
    if (quote_type == '\'')
    {
        free(accumulator); // Free the initial empty string
        accumulator = singel_quotes_handler(start);
        return accumulator;
    }
    
    // Double quotes handling
    while (*end && *end != '"')
    {
        if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '_' || *(end + 1) == '?'))
        {
            end++;
            if (*end == '?')
            {
                // Handle $? by getting the exit status
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
                // Find the end of the variable name
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
    
    if (*end != '"') // Unclosed double quote
    {
        free(accumulator);
        return NULL;
    }
    *start = end + 1; // Move past the closing double quote
    return accumulator;
}

// Handles double-quoted dollar signs
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

// Handles the question mark for exit status
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

// Handles regular dollar signs for variable expansion
static char *handle_regular_dollar(char **end, char **env, int ex_status, char *accumulator)
{
    char *var_start = *end;
    
    // Find the end of the variable name
    while (**end && (ft_isalnum(**end) || **end == '_' || **end == '?') && \
            **end != ' ' && **end != '\t' && **end != '|' && \
            **end != '<' && **end != '>' && **end != '\'' && **end != '"')
        (*end)++;
    return Handle_regular_accumualtor(var_start, *end, env, accumulator);
}

// Handles dollar cases (variable expansion, exit status, etc.)
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

// Handles normal characters by accumulating them
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

// Handles unquoted parts of the input
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

// Processes a segment of the input (quoted or unquoted)
static char *process_segment(char **start, int *quotes_type, char **env, int ex_status)
{
    if (**start == '\'' || **start == '"')
        return handle_quoted_part(start, quotes_type, env, ex_status);
    else
        return handle_unquoted_part(start, quotes_type, env, ex_status);
}

// Handles words by accumulating segments
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

// Tokenizes the input line
t_token *tokenize(char *line, char **my_env, int ex_status)
{
    t_token *tokens = NULL;
    char *start = line;
    int quotes_type = 0;

    while (*start)
    {
        // Skip whitespace
        while (*start == ' ' || *start == '\t')
            start++;
        if (!*start)
            break;
            
        if (*start == '|' || *start == '<' || *start == '>')
        {
            // Handle operators
            t_token *token = handle_operator(&start, quotes_type);
            if (!token)
                return free_tokens(tokens), NULL;
            add_token(&tokens, token);
        }
        else
        {
            // Handle words
            t_token *token = handle_word(&start, &quotes_type, my_env, ex_status);
            if (!token)
                return free_tokens(tokens), NULL;
            add_token(&tokens, token);
        }
    }
    return tokens;
}