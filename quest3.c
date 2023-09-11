#include <stdio.h>
#include <unistd.h>

/*

Yes, I can let the child process print first by using sleep() instead of wait().


*/
int main() {
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        printf("hello\n");
    } else if (pid > 0) {  // Parent process
        sleep(5);  // Sleep to allow the child to print first
        printf("goodbye\n");
    } else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}
