#include <stdio.h>
#include <unistd.h>    // Required for fork(), getpid(), getppid()
#include <sys/types.h> // Required for pid_t

int main()
{
    pid_t process_id;

    printf("--- Before forking ---\n");
    printf("This is the main process. PID: %d\n\n", getpid());

    // Create a new process
    process_id = fork();

    // After this point, there are two processes executing this code.

    if (process_id < 0)
    {
        // --- Error Condition ---
        // fork() returns -1 if it fails to create a child process.
        fprintf(stderr, "Fork failed!\n");
        return 1; // Exit with an error code
    }
    else if (process_id == 0)
    {
        // --- Child Process ---
        // fork() returns 0 to the newly created child process.
        printf("Hello from the CHILD process! 👧\n");
        printf("My PID is: %d\n", getpid());
        printf("My Parent's PID is: %d\n", getppid());
    }
    else
    {
        // --- Parent Process ---
        // fork() returns the child's PID to the parent process.
        printf("Hello from the PARENT process! 👨‍👩‍👧\n");
        printf("My PID is: %d\n", getpid());
        printf("I created a child with PID: %d\n", process_id);
    }

    printf("\n--- Both processes will print this line. ---\n");
    printf("Executing process PID: %d\n");

    return 0;
}