/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:34:06 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/28 22:27:08 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"
#include "header.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"

static char *expand_heredoc_line(char *line, char **env, int ex_status)
{
    char    *result;
    char    *current;
    int     quotes_type = 0; // Unquoted context for heredoc

    result = NULL;
    current = line;
    while (*current)
    {
        if (*current == '$' && (ft_isalpha(*(current + 1)) || 
            *(current + 1) == '?' || *(current + 1) == '_'))
        {
            result = handle_dollar_case(&current, env, ex_status, result);
        }
        else
        {
            result = handle_normal_char(&current, result);
        }
    }
    if(result)
        return result;
    return ft_strdup("");		
}

static void heredoc_sigint_handler(int sig)
{
    (void)sig;
    exit(130);
}

static void heredoc_child_process(int pipe_write_fd, t_command *cmd, 
                                char **envp, int ex_status)
{
    char    *line;
    char    *expanded;

    signal(SIGINT, heredoc_sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, cmd->heredoc_delimiter) == 0)
        {
            free(line);
            break;
        }
        if (cmd->heredoc_quotes == 0)  // Only expand if delimiter was unquoted
        {
            expanded = expand_heredoc_line(line, envp, ex_status);
            if (expanded)
            {
                ft_putendl_fd(expanded, pipe_write_fd);
                free(expanded);
            }
            else
                ft_putendl_fd(line, pipe_write_fd);
        }
        else
        {
            ft_putendl_fd(line, pipe_write_fd);  // No expansion for quoted delimiter
        }
        free(line);
    }
    close(pipe_write_fd);
    exit(0);
}
