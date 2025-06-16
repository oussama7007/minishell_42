#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork(); // create child

    if (pid == 0)
    {
        // This is the child process
        printf("I am the child (PID: %d), PID2 = %d\n", getpid(), pid);
    }
    else
    {
        // This is the parent process
        printf("I am the parent (PID: %d), child PID: %d\n", getpid(), pid);
       // wait(NULL); // wait for the child to finish
    }

    return 0;
}
