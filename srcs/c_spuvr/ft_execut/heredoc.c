/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:34:06 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/01 14:39:43 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"
// char expand_herdoc_line(char *line, char **env, int ex_status)
static char *expand_heredoc_line(char *line, char **env, t_data *data)
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
            result = handle_dollar_case(&current, env,  result, data);
        }
        else
        {
            result = handle_normal_char(&current, result, data);
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

static void	heredoc_child_process(int pipe_write_fd, t_command *cmd, char **envp,t_data *data)
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
			word = expand_heredoc_line(line, envp , data);
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

int	setup_heredoc(t_command *cmd, char **envp,t_data *data)
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
		heredoc_child_process(pipe_fds[1], cmd, envp, data);
	}
	return (heredoc_parent_process(pid, pipe_fds));
}
