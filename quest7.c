#include <stdio.h>
#include <unistd.h>
/*

 when the child process calls printf after closing the descriptor,
 nothing is printed to the standard output because stdout has been closed in the child process.

*/





int main() {
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        close(STDOUT_FILENO);  // Close stdout
        printf("This won't be printed\n");
    } else if (pid > 0) {  // Parent process
        printf("Parent process\n");
    } else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}
