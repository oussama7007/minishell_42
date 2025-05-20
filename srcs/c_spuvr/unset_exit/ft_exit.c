/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:22:45 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/20 16:43:47 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static int is_numeric_arg(char *str)
{
    int i;

    i = 0;
    if (str[0] == '+' || str[0] == '-')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

// Free your token linked list
static void n_free_tokens(t_token *tokens)
{
    t_token *current;
    t_token *next;

    current = tokens;
    while (current)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

// Free your command linked list
static void free_commands(t_command *cmd)
{
    t_command *current;
    t_command *next;
    int i;

    current = cmd;
    while (current)
    {
        next = current->next;
        
        // Free command name
        free(current->cmd);
        
        // Free args array
        i = 0;
        if (current->args)
        {
            while (current->args[i])
                free(current->args[i++]);
            free(current->args);
        }
        
        // Free redirections
        i = 0;
        if (current->red_in)
        {
            while (current->red_in[i])
                free(current->red_in[i++]);
            free(current->red_in);
        }
        
        i = 0;
        if (current->red_out)
        {
            while (current->red_out[i])
                free(current->red_out[i++]);
            free(current->red_out);
        }
        
        free(current->append);
        free(current->heredoc_delimiter);
        free(current);
        current = next;
    }
}

int ft_exit(char **args, char ***env_ptr, t_token *tokens, t_command *commands, int last_status)
{
    long long exit_code;
    
    //ft_putendl_fd("exit", 2);
    
    if (!args[1])
    {
        // No arguments - exit with last status
        //rl_clear_history();
        free_environment(*env_ptr);
        n_free_tokens(tokens);
        free_commands(commands);
        exit(last_status);
    }
    
    if (!is_numeric_arg(args[1]))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putendl_fd(": numeric argument required", 2);
        
        //rl_clear_history();
        free_environment(*env_ptr);
        n_free_tokens(tokens);
        free_commands(commands);
        exit(255);
    }
    
    if (args[2])
    {
        // Too many arguments
        ft_putendl_fd("minishell: exit: too many arguments", 2);
        return (1);
    }
    
    exit_code = ft_atoi(args[1]) % 256;
    
    //rl_clear_history();
    free_environment(*env_ptr);
    n_free_tokens(tokens);
    free_commands(commands);
    exit((int)exit_code);
}
