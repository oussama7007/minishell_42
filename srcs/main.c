/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/25 15:26:09 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "c_spuvr/built_functions.h"
#include <readline/readline.h>
#include <readline/history.h>

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
    while (tokens)
    {
        type = tokens->type;
        next = tokens->next;
        if (type == TOKEN_PIPE && next == NULL)
            return(error(ERR_PIPE), 0);
        if (type >= TOKEN_PIPE  && !next)
            return(error(ERR_NEWLINE), 0);
        if (next && type >= TOKEN_PIPE  && next->type >= TOKEN_PIPE )
            return(error(ERR_SYNTAX), 0);
        tokens = tokens->next;
    }
    return (1);
}

static void    print_tokens(t_token *tokens)
{
    while(tokens)
    {
        printf(" type : %d, value %s , quotes type %d\n", 
               tokens->type, tokens->value, tokens->quotes_type);
        tokens = tokens->next;
    }
}

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
void    sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n",1);
    rl_on_new_line();
    //rl_replace_line("", 0);
    rl_redisplay();
}
void    setup_signal_handlers(void)
{
    
    write(1, "\n", 1);
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN); // TEST IT BEHAVIOR 
    
}
int main(int ac, char **av, char **env)
{
    setup_signal_handlers();// hada rah dyali o lakhour maereftch lach zetih mhm test hada o dyalk rah kanden khedam dyali mzn 
    char        **my_envp;
    char        *line;
    int         ex_status;
    t_token     *tokens = NULL;
    t_command   *commands;
    
    my_envp = init_environment(env);
    ensure_minimal_env(&my_envp);
    my_setenv("_", av[0], &my_envp);
   // setup_signals();
    ex_status = 0;
    while (1)
    {
        line = readline("Minishell$ ");
        if (!line)
        {
            write(1, "exit\n", 5);
            free_environment(my_envp);
            //rl_clear_history();
            exit(ex_status);
        }
        if (*line)
            add_history(line);
        if (!handle_quotes(line) || !check_invalid_char(line))
        {
            if (!handle_quotes(line))
                write(2, "Minishell: Quotes aren't closed\n", 33);
            else
                write(2, "Minishell: Invalid character \n", 30);
            free(line);
            continue;
        }
        tokens = tokenize(line, my_envp, ex_status);
        if (!tokens || !*line)
        {
            
            free(line);
            continue;
        }
        if (!validate_syntax(tokens))
        {
            free(line);
            free_tokens(tokens);
            continue;
        }
        
       
        commands = build_command(tokens);
        print_commands(commands);
		if (commands == NULL)
		{
			free(line);
			free_tokens(tokens);
			continue;
		}
        else if (commands && commands->cmd && ft_strcmp(commands->cmd, "exit") == 0)
        {
            ex_status = ft_exit(commands->args, &my_envp, commands, tokens, ex_status);
            // ft_exit will only return if there are too many arguments.
            // In that case, we fall through to the regular cleanup for this loop iteration.
        }
        
        else if (commands)
        {
 
            ex_status = ft_execute_command_list(commands, &my_envp);
            free_command(commands); // Free the commands list after execution
   
        }
        print_tokens(tokens);
        free_tokens(tokens);
        free(line);
    }
    
    free_environment(my_envp); // Cleanup the custom environment
    //rl_clear_history();         // Cleanup readline history memory
    return (ex_status);
}
// you need to handle | > maybe or |<
// when you pass "" or '' should output command not found