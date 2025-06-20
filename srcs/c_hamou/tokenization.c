/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 02:12:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/20 16:16:18 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
static char *Handle_regular_accumualtor(char *var_name, char *end, char *var_start, char **env, char *accumulator)
{
    char *tmp;
    char *var_value;
    char *temp;
    
    var_name = ft_strndup(var_start, end - var_start);
    var_value = get_var_value(var_name, env);
    temp = accumulator;
    accumulator = ft_strjoin(temp, var_value);    
    return(free(temp),free(var_name),accumulator);
}
static char *qestion_mark(int ex_status)
{
    char *tmp;

    tmp = ft_itoa(ex_status);
    return tmp;
}
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
    *start = end;
    return (free(word),token);
}
static int     get_quotes_type(char quote_type)
{
    int quotes_type;
    if(quote_type == '"')
        quotes_type = 2;
    else
        quotes_type = 1;
    return (quotes_type);
}
static char *singel_quotes_handler(char **start)
{
    char *tmp;
    char *accumulator;
    char *end;

    end = *start;
    while(*end && *end != '\'')
        end++;
    if (*end != '\'') // Closing quote not found!
        return NULL; 
    accumulator = ft_strndup(*start, end - *start);
    end++; //skip closing quotes 
    *start = end;
    return accumulator;
}
static char *handle_quoted_part(char **start, int *quotes_type, char **env, int ex_status)
{
    char quote_type = **start;
    char *end;
    char *accumulator;
    char *tmp;
    char *var_name;
    char *var_value;
    char chr_str[2] = {0, 0};

    accumulator = NULL;
     *quotes_type = get_quotes_type(quote_type);
    
    (*start)++;
    end = *start;
    if (quote_type == '\'')
        accumulator = singel_quotes_handler(start);
    else // Double quotes
    {
        while (*end && *end != quote_type)
        {
            if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '_' || *(end + 1) == '?'))
            {
                end++;
                if(*end == '?')
                {
                    accumulator = ft_strjoin(accumulator, qestion_mark(ex_status));
                    end++;
                }
                char *var_start = end;
                while (*end && *end != quote_type && (ft_isalnum(*end) || *end == '_' || *end == '?')) //TEST ?
                    end++;
                accumulator = Handle_regular_accumualtor(var_name, end, var_start, env, accumulator);
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

static char *accumulator_unquote_part(char **env, char **end, char *quote_start, char *accumulator)
{
    char *quoted;
    char *expanded;
    char *tmp;
    char *new_accumulator;
    
    quoted =  ft_strndup(quote_start, *end - quote_start);
    expanded = expand_value_func(quoted, env);
    tmp = accumulator;
    new_accumulator = ft_strjoin(tmp, expanded);
    (*end)++;
    return(free(quoted), free(tmp), free(expanded), new_accumulator);
}

static char *handle_question_mark(char **end, int ex_status, char *accumulator)
{
	char	*tmp;
	tmp = accumulator;
	accumulator = ft_strjoin(tmp, qestion_mark(ex_status));
	(*end)++;
	return (free(tmp), accumulator);
}
static char *handle_double_quote_dollar(char **end, char *accumulator, char **env)
{
    char *tmp;
    char *quote_start;
    
    
    quote_start = *end;
    (*end)++;
    while(**end && **end !='"')
        (*end)++;
    accumulator = accumulator_unquote_part(env, end, quote_start, accumulator);
    if(!accumulator)	
		return (NULL);
	return (accumulator); 
}
static char *handle_regular_accumulator(char *end, char *var_start, char **env, char *accumulator)
{
    char *tmp;
    char *var_value;
    char *temp;
    char *var_name;

    var_name = ft_strndup(var_start, end - var_start);
    var_value = get_var_value(var_name, env);
    tmp = accumulator;
    accumulator = ft_strjoin(tmp, var_value);
    return(free(tmp), free(var_name), accumulator);
}
static char *handle_regular_dollar(char **end, char **env, int ex_status, char *accumulator)
{
    char *var_start;
    
    var_start = *end;
    while (**end && (ft_isalnum(**end) || **end == '_' || **end == '?') && \
			**end != ' ' && **end != '\t' && **end != '|' && \
			**end != '<' && **end != '>' && **end != '\'' && **end != '"')
    (*end)++;
    accumulator = handle_regular_accumulator(*end, var_start, env, accumulator);
    return(accumulator);
}
static char *handle_dollar_case(char **end, char **env, int ex_status, char *accumulator)
{   
    (*end)++;
    if(**end == '?')
     	accumulator = handle_question_mark(end, ex_status, accumulator);
    else if(**end == '"')
        accumulator = handle_double_quote_dollar(end, accumulator, env);
    else
		accumulator = handle_regular_dollar(end, env, ex_status, accumulator);
	return (accumulator);

}
static char	*handle_normal_char(char **end_ptr, char *accumulator)
{
	char	*end;
	char	*tmp;
	char	chr_str[2];

	end = *end_ptr;
	chr_str[0] = *end;
	chr_str[1] = '\0';
	tmp = accumulator;
	accumulator = ft_strjoin(tmp, chr_str);
	free(tmp);
	end++;
	*end_ptr = end;
	return (accumulator);
}
static char *handle_unquoted_part(char **start, int *quotes_type, char **env, int ex_status)
{
    char *accumulator;
    char *end;

    end = *start;
    accumulator = NULL;
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
    if (!accumulator)
        accumulator =  ft_strdup("");
   
    return accumulator;
}

static t_token *handle_word(char **start, int *quotes_type , char **my_env, int ex_status)
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
            segment = handle_quoted_part(start, quotes_type, my_env, ex_status);
        else
            segment = handle_unquoted_part(start, quotes_type, my_env, ex_status);
        if (!segment)
            return (free(accumulator), NULL);
        tmp = accumulator;
        accumulator = ft_strjoin(tmp, segment);
        if (!accumulator)
            return (free(segment),free(tmp),NULL); 
    }
    if(accumulator)
    {
        token = new_token(get_token_type(accumulator), accumulator, *quotes_type);
        return (free(segment),free(tmp),free(accumulator), token);
    }
    return (free(segment),free(tmp),free(accumulator),NULL);
}
t_token     *tokenize(char *line, char **my_env, int ex_status)
{
    t_token *tokens = NULL;
    char *start = line;
    t_token *token;
    int quotes_type = 0;

    while (*start)
    {
        while (*start && (*start == ' ' || *start == '\t'))
            start++;
        if (*start == '|' || *start == '<' || *start == '>')
        {
            token = handle_operator(&start, quotes_type);
            if (!token)
                return (free_tokens(tokens), NULL);
            add_token(&tokens, token);
        }
        else if(*start) // Check if there's still input to process
        {
            token = handle_word(&start, &quotes_type, my_env, ex_status);
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