/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/24 15:08:50 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "c_spuvr/built_functions.h"
 
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
    else 
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
        if(type >= TOKEN_PIPE  && !next)
            return(error(ERR_NEWLINE), 0);
        if(next && type >= TOKEN_PIPE   && next->type >= TOKEN_PIPE )
            return(error(ERR_SYNTAX), 0);
        tokens = tokens->next;
    }
    return 1;
}
// static void    print_tokens(t_token *tokens)
// {
//     while(tokens)
//     {
//         printf(" type : %d, value %s \n", tokens->type, tokens->value);
//         tokens = tokens->next;
//     }
// }


static void print_commands(t_command *commands)
{
    while (commands)
    {
        printf("cmd : %s\n", commands->cmd);
        printf("-------------------------------------------------------------cmd\n");

        int i = -1;
        while (commands->args && commands->args[++i])
            printf(" --- args --- : %s\n", commands->args[i]);

        printf("-------------------------------------------------------------args\n");
        i = -1;
        while (commands->red_in && commands->red_in[++i])
            printf("+++ red_in : %s\n", commands->red_in[i]);

        printf("-------------------------------------------------------------red_in\n");
        i = -1;
        while (commands->red_out && commands->red_out[++i])
        {
            printf("-- red_out-- : %s", commands->red_out[i]);
            if (commands->append)
                printf("  (append: %s)\n", commands->append[i] ? "yes" : "no");
            else
                printf("\n");
        }

        if (commands->heredoc_delimiter)
            printf("<<< heredoc delimiter : %s\n", commands->heredoc_delimiter);

        printf("=============================================================\n\n");
        commands = commands->next;
    }
}
int     check_single_quotes(char *line, int *i)
{
    (*i)++;
    while(line[*i])
    {
        if(line[*i] == '\'')
            return 1;
        (*i)++;
    }
    return 0;
}
int     check_double_quotes(char *line, int *i)
{
    (*i)++;
    while(line[*i])
    {
        if(line[*i] == '"')
            return 1;
        (*i)++;
    }
    return 0;
}
int     handle_quotes(char *line)
{
    int i;
    i = -1;
    while(line[++i])
    {
        if(line[i] == '\'')
        {
                if(!check_single_quotes(line, &i))
                    return(0);
        }
        if(line[i] == '"')
        { 
            if(!check_double_quotes(line, &i))
                return 0;
        }
    }
    return 1;
}
static void    t()
{
    system("leaks a.out");
}
int     check_invalid_char(char *line)
{
    int i;
    i = -1;
    while(line[++i])
    {
        if(line[i] == ';' || line[i] == 92)
            return 0;
    }
    return 1;
}
// void    add_ptr_node(t_head_list **head, void *ptr)
// {
//     t_gc_list *node;

//     node = malloc(sizeof(t_gc_list));
//     if(!node)
//         return;
//     node->ptr = ptr;
//     node->next = *head;
//     (*head) = node;
// }
// void *gc_malloc(t_head_list **head,int size)
// {
//     void *ptr;

//     ptr = malloc(size);
//     if(!ptr)
//         return NULL;
//     add_ptr_node(head, ptr);
//     return ptr;
// }
// void    free_gc(t_head_list **head)
// {
//     t_head_list *tmp;
//     t_head_list *next;
//     if(head)
//     {
//         tmp = *head;
//         while(tmp)
//         {
//             next = tmp->next;
//             free(tmp->ptr);
//             free(tmp);
//             tmp = next;
//         }
//         head = NULL;
//     }
// }
int main(int ac, char **av, char **env)
{
    char	**my_envp;
    char *line;
    int     ex_status;
    t_token *tokens;
    t_command *commands;
   // t_head_list *head = NULL;
    
    
    (void)ac;
    (void)av;
    my_envp = init_environment(env);
    while(1)
    {
        line = readline("Minishell$ ");
        if(!line)
        {
            write(1,"exit\n",5);
            free_environment(my_envp);
            exit(0);
        }
        if(*line)
            add_history(line);
        if(!handle_quotes(line) || !check_invalid_char(line))
        {
            
            if(!handle_quotes(line))
                write(2, "Minishell: Quotes aren't closed\n", 33);
            else
                write(2, "Minishell: Invalid character\n", 30);
            free(line);
            continue;
        }
        tokens = tokenize( line); 
        if(!tokens || !*line)
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
        commands = build_command(tokens);
        if (commands)
        {
            ex_status = ft_execute_command_list(commands, &my_envp);
        }

        // print_commands(commands);

        // print_tokens(tokens); // for dubg
        // print_commands(commands);

        free_tokens(tokens);
        free(line);
    }
    exit(0);
}

// need to handle  quotes " " '' 
// Tokenizes input (done). 
// Validates syntax (done).
// Builds commands (t_command) for execution (missing).
// Handles quotes and expansions (missing).
// Reports syntax errors with minishell: prefix and sets $? = 2 (missing).
 