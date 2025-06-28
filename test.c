/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:34:06 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/27 18:18:36 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static char *expand_heredoc_line(char *line, char **envp, int ex_status)
{
    char *result;
    int i;
    int j;

    result = malloc(ft_strlen(line) * 4 + 1); // Large initial buffer
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == '$' && (ft_isalpha(line[i + 1]) || line[i + 1] == '?'))
        {
            i++;
            if (line[i] == '?')
            {
                char *status_str = ft_itoa(ex_status);
                ft_strcpy(&result[j], status_str);
                j += ft_strlen(status_str);
                free(status_str);
                i++;
            }
            else
            {
                char *var_start = &line[i];
                while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
                    i++;
                char *var_name = ft_strndup(var_start, &line[i] - var_start);
                char *var_value = get_var_value(var_name, envp);
                if (var_value)
                {
                    ft_strcpy(&result[j], var_value);
                    j += ft_strlen(var_value);
                }
                free(var_name);
            }
        }
        else
            result[j++] = line[i++];
    }
    result[j] = '\0';
    return (result);
}

static void heredoc_sigint_handler(int sig)
{
    (void)sig;
    exit(130);
}

static void heredoc_child_process(int pipe_write_fd, t_command *cmd, char **envp, int ex_status)
{
    char *line;
    char *expanded;

    signal(SIGINT, heredoc_sigint_handler);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, cmd->heredoc_delimiter) == 0)
        {
            if (line)
                free(line);
            break;
        }
        if (cmd->heredoc_expand)
            expanded = expand_heredoc_line(line, envp, ex_status);
        else
            expanded = ft_strdup(line);
        if (expanded)
        {
            ft_putendl_fd(expanded, pipe_write_fd); // Adds newline, matching readline behavior
            free(expanded);
        }
        free(line);
    }
    close(pipe_write_fd);
    exit(0);
}

static int heredoc_parent_process(pid_t pid, int *pipe_fds)
{
    int status;

    signal(SIGINT, SIG_IGN);
    close(pipe_fds[1]);
    waitpid(pid, &status, 0);
    setup_signals();
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        return (pipe_fds[0]);
    close(pipe_fds[0]);
    return (-1);
}

int setup_heredoc(t_command *cmd, char **envp, int ex_status)
{
    int pipe_fds[2];
    pid_t pid;

    if (!cmd->heredoc_delimiter)
        return (-1);
    if (pipe(pipe_fds) == -1)
        return (handle_fork_error(NULL));
    pid = fork();
    if (pid == -1)
    {
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        return (handle_fork_error(NULL));
    }
    if (pid == 0)
    {
        close(pipe_fds[0]);
        heredoc_child_process(pipe_fds[1], cmd, envp, ex_status);
    }
    return (heredoc_parent_process(pid, pipe_fds));
}