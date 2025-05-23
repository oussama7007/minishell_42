// In redirections.c
#include "../built_functions.h" // Or your main execution header

// Forward declaration if needed, or include relevant headers for open, dup2, close, STDIN_FILENO, etc.
// #include <fcntl.h>
// #include <unistd.h>

void handle_redirections_for_child(t_command *cmd_node)
{
    int fd_in = -1;
    int fd_out = -1;

    // Input redirection: ">" or ">>"
    // You'll need to iterate if you support multiple output redirections,
    // but the last one usually takes precedence. Let's assume one for now from cmd_node.
    if (cmd_node->red_out && cmd_node->red_out[0]) // Assuming red_out is char** and append is also an array/flags
    {
        // Check cmd_node->append[0] (or however you store if it's append or truncate)
        if (cmd_node->append && cmd_node->append[0]) // Simplified: assuming append[0] corresponds to red_out[0]
            fd_out = open(cmd_node->red_out[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd_out = open(cmd_node->red_out[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (fd_out == -1)
        {
            perror("minishell: open output file"); // Error handling
            exit(1); // Child exits on redirection error
        }
        if (dup2(fd_out, STDOUT_FILENO) == -1)
        {
            perror("minishell: dup2 stdout");
            exit(1);
        }
        close(fd_out);
    }

    // Input redirection: "<"
    if (cmd_node->red_in && cmd_node->red_in[0])
    {
        fd_in = open(cmd_node->red_in[0], O_RDONLY);
        if (fd_in == -1)
        {
            perror("minishell: open input file");
            exit(1); // Child exits
        }
        if (dup2(fd_in, STDIN_FILENO) == -1)
        {
            perror("minishell: dup2 stdin");
            exit(1);
        }
        close(fd_in);
    }
    // Note: Heredoc (<<) will be a bit different, often involving a temp file or pipe.
    // We can tackle that after basic <, >, >>.
}