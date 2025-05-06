/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:18:20 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/06 17:27:01 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H
# include <unistd.h>
# include <stdlib.h>

// --- Redirection Types ---
// gotta know if its < > << >> right? enum is clean.
typedef enum e_redir_type
{
    REDIR_IN,       // <
    REDIR_OUT,      // >
    REDIR_HEREDOC,  // <<
    REDIR_APPEND    // >>
}   t_redir_type;

// --- Redirection Node ---
// commands can have loads of these, so link em up
typedef struct s_redir
{
    t_redir_type      type;       // which one from the enum?
    char              *filename;  // the file name, or the word for <<
    struct s_redir    *next;      // next redir for the *same* command
}   t_redir;

// --- Command Node Types ---
// gotta know if its a command or just a pipe symbol
typedef enum e_node_type
{
    NODE_COMMAND,   // somethin' to run, like 'ls'
    NODE_PIPE       // just the '|' symbol connectin' things
    // NODE_AND, NODE_OR // maybe later if needed
}   t_node_type;

// --- Main Command/Pipe Node ---
// this is the main chain: cmd -> pipe -> cmd -> ...
typedef struct s_node
{
    t_node_type       type;         // command or pipe? check the enum
    char              **args;       // the actual command and its flags/args, like {"ls", "-l", NULL}. NULL if its just a pipe node.
    t_redir           *redirections;// head of the linked list of t_redir for *this* command node
    struct s_node     *next;        // the next node in the chain (pipe or command)
}   t_node;


char	*ft_strdup(char *s);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif // MINISHELL_STRUCTS_H
// --- End of File ---