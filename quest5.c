#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*


 The wait() system call is used in the parent process to wait for the child process to finish.
 It returns the exit status of the child process. If WIFEXITED(status) is true, it means the child process exited normally,
 and WEXITSTATUS(status) returns the exit status of the child.

 Using wait() in the child would not be meaningful because it is designed for the parent process to wait for its
 child processes.


*/

int main() {
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        printf("Child process\n");
    } else if (pid > 0) {  // Parent process
        int status;
        wait(&status);  // Wait for the child to finish

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    } else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}

