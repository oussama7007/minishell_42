#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	// The key line: clear_undo is 0.
	// This does NOT add the replacement to the undo list.
	rl_replace_line("", 1);
	rl_redisplay();
}

int	main(void)
{
	char	*line;

	signal(SIGINT, sigint_handler);
	printf("--- TEST: clear_undo = 0 (Undo is PRESERVED) ---\n");
	printf("1. Type 'hello'.\n");
	printf("2. Press Ctrl+C.\n");
	printf("3. Type 'world'.\n");
	printf("4. Press Ctrl+_ (Control + Underscore) to undo.\n");
	printf("5. Observe that 'world' is removed.\n\n");
	while (1)
	{
		line = readline("prompt> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		free(line);
	}
	return (0);
}