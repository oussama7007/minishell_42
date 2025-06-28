/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:34:06 by oadouz            #+#    #+#             */
/*   Updated: 2025/06/28 04:12:54 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"
// kayna fih chwiya d lkhedma mhm dik nahr o ness 
// fo9ach ghan pushiw ?? 
// dir expending dialek henaiaaaa

static char	*expand_heredoc_line(char *line, char **envp)
{
	(void)envp; // fach tbghi dir expend 7ayed hadi 
	// Variable expansion Neta li khassek dirha ;) 
	return (ft_strdup(line));
}

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	exit(130);
}

static void	heredoc_child_process(int pipe_write_fd, t_command *cmd, char **envp)
{
	char	*line;
	char	*expanded;

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
		expanded = expand_heredoc_line(line, envp);÷
		ft_putendl_fd(expanded, pipe_write_fd);
		free(line);
		free(expanded);
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

int	setup_heredoc(t_command *cmd, char **envp)
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
		heredoc_child_process(pipe_fds[1], cmd, envp);
	}
	return (heredoc_parent_process(pid, pipe_fds));
}
