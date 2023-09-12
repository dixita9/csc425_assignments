#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/*

 waitpid() is useful when you want to wait for a specific child process, and it provides more control over which process you
 are waiting for compared to wait(). You can specify the child's PID as the first argument

*/
int main() {
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        printf("Child process\n");
    } else if (pid > 0) {  // Parent process
        int status;
        waitpid(pid, &status, 0);  // Wait for the specific child process

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    } else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}
