#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGINT
void handle_sigint(int sig) {
    printf("\nCaught SIGINT (Ctrl+C), signal number: %d\n", sig);
    printf("Continuing execution...\n");
}

int main(void) {
    // Set the SIGINT handler
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("Failed to set SIGINT handler");
        return 1;
    }

    // Set SIGQUIT to be ignored
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR) {
        perror("Failed to ignore SIGQUIT");
        return 1;
    }

    printf("Running... Press Ctrl+C to trigger SIGINT or Ctrl+\\ to test SIGQUIT.\n");

    // Infinite loop to keep the program running
    while (1) {
        printf("Working...\n");
        sleep(01);
    }

    return 0;
}
