/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/12 02:24:53 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"








void    error(int type)
{
    if (type == ERR_PIPE)
        write(2, "Minishell: syntax error near unexpected token `|'\n", 50);
    else if (type == ERR_SEMICOLON)
        write(2, "Minishell: syntax error near unexpected token `;'\n", 51);
    else if (type == ERR_NEWLINE)
        write(2, "Minishell: syntax error near unexpected token `newline'\n", 57);
    else if (type == ERR_SYNTAX)
        write(2, "Minishell: syntax error \n", 26);
}
int     validate_syntax(t_token *tokens)
{
    int type;
    t_token *next;
    while(tokens)
    {
        type = tokens->type;
        next = tokens->next;
        if(type == TOKEN_PIPE && next == NULL)
            return(error(ERR_PIPE), 0);
        if((type >= TOKEN_PIPE && type <= TOKEN_SEMICOLON ) && !next)
            return(error(ERR_NEWLINE), 0);
        if(next && (type >= TOKEN_PIPE && type <= TOKEN_SEMICOLON ) && (next->type >= TOKEN_PIPE && next->type <= TOKEN_SEMICOLON))
            return(error(ERR_SYNTAX), 0);
        tokens = tokens->next;
    }
    return 1;
}
void    print_tokens(t_token *tokens)
{
    while(tokens)
    {
        printf(" type : %d, value %s \n", tokens->type, tokens->value);
        tokens = tokens->next;
    }
    
}

void    t()
{
    system("leaks a.out");
}
int main()
{
    char *line;
    t_token *tokens;
    t_command *commands;
    
    atexit(t);
    while(1)
    {
        line = readline("Minishell$ ");
        if(!line)
        {
            write(1,"exit\n",5);
            exit(0);
        }
        if(*line)
            add_history(line);
        tokens = tokenize(line); 
        if(!tokens)
        {
            free(line);
            continue;
        }
        if(!validate_syntax(tokens))
        {
            free(line);
            free_tokens(tokens);
            continue;
        }
        print_tokens(tokens); // for dubg
        //commands = build_command(tokens);
        free_tokens(tokens);
        free(line);
    }
    exit(0);
}


// Tokenizes input (done). 
// Validates syntax (done).
// Builds commands (t_command) for execution (missing).
// Handles quotes and expansions (missing).
// Reports syntax errors with minishell: prefix and sets $? = 2 (missing).
