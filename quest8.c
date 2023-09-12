#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Include the wait header
/*

 This program creates two child processes. The first child closes its standard output and writes data to a pipe,
 which is read by the second child. This demonstrates interprocess communication using pipes.
 The parent waits for both child processes to finish using wait(NULL).


*/
int main() {
    int pipefd[2];
    pid_t child1, child2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create the first child
    if ((child1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) {
        // Child 1: Closes standard output (STDOUT FILENO)
        close(pipefd[0]); // Close the read end of the pipe
        close(STDOUT_FILENO); // Close standard output
        dup(pipefd[1]); // Redirect stdout to the write end of the pipe
        close(pipefd[1]); // Close the original write end of the pipe

        // Now child 1 can write to the pipe, and its output will be sent to child 2

        printf("Child 1: Sending data to Child 2\n");
        // Write data to the pipe
        char message[] = "Hello from Child 1!";
        write(STDOUT_FILENO, message, sizeof(message));

        // Close the redirected stdout (write end of the pipe)
        close(STDOUT_FILENO);

        exit(EXIT_SUCCESS);
    }

    // Create the second child
    if ((child2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child2 == 0) {
        // Child 2: Reads data from the pipe

        close(pipefd[1]); // Close the write end of the pipe

        // Redirect stdin to read from the pipe
        close(STDIN_FILENO); // Close standard input
        dup(pipefd[0]); // Redirect stdin to the read end of the pipe
        close(pipefd[0]); // Close the original read end of the pipe

        printf("Child 2: Receiving data from Child 1\n");

        // Read and display data from the pipe
        char buffer[100];
        int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));

        if (bytes_read > 0) {
            printf("Child 2 received: %s\n", buffer);
        } else {
            printf("Child 2: No data received.\n");
        }

        // Close the redirected stdin (read end of the pipe)
        close(STDIN_FILENO);

        exit(EXIT_SUCCESS);
    }

    // Parent process
    close(pipefd[0]); // Close the unused read end of the pipe
    close(pipefd[1]); // Close the unused write end of the pipe

    // Wait for both child processes to finish
    wait(NULL);
    wait(NULL);

    return 0;
}

