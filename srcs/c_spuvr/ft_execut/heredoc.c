/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:34:06 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/29 16:40:43 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"
// kayna fih chwiya d lkhedma mhm dik nahr o ness 
// fo9ach ghan pushiw ?? 
// dir expending dialek henaiaaaa



// char expand_herdoc_line(char *line, char **env, int ex_status)
static char *expand_heredoc_line(char *line, char **env, int ex_status)
{
    char    *result;
    char    *current;
    int     quotes_type = 0; // Unquoted context for heredoc
	int delimiter = 0;
    result = NULL;
    current = line;
    while (*current)
    {
        if (*current == '$' && (ft_isalpha(*(current + 1)) || 
            *(current + 1) == '?' || *(current + 1) == '_'))
        {
            result = handle_dollar_case(&current, env, ex_status, result, &delimiter);
        }
        else
        {
            result = handle_normal_char(&current, result, &delimiter);
        }
    }
    if(result)
		return result;
	return ft_strdup("");		
}

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	exit(130);
}

static void	heredoc_child_process(int pipe_write_fd, t_command *cmd, char **envp, int ex_status)
{

	char	*line;
	char	*word = NULL;

	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->heredoc_delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		if(cmd->heredoc_quotes == 0)
		{
			word = expand_heredoc_line(line, envp , ex_status );	
			if(word)
			{	
				ft_putendl_fd(word, pipe_write_fd);
				free(word);
			}
			else
			{
				ft_putendl_fd(line, pipe_write_fd);
		    	free(line);
			}
		}
		else
		{
			ft_putendl_fd(line, pipe_write_fd);
		    free(line);
		}
	}
	close(pipe_write_fd);
	exit(0);
}

static int	heredoc_parent_process(pid_t pid, int *pipe_fds)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	close(pipe_fds[1]);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (pipe_fds[0]);
	close(pipe_fds[0]);
	return (-1);
}

int	setup_heredoc(t_command *cmd, char **envp, int ex_status)
{
	int		pipe_fds[2];
	pid_t	pid;
    
	//printf("%s\n", cmd);
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
