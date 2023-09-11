#include <stdio.h>
#include <unistd.h>
/*                  


 When we call fork() in a program, it creates a new child process that is a duplicate of the parent process.
 This includes duplicating the parent's memory space. However, the child process gets its own copy of the parent's memory,
 and any changes made in one process will not affect the other.

 Before calling fork(), the main process sets a variable x to 100, so the child process will also have its own separate copy
 of x, initially set to 100. Both the parent and child processes have their own independent memory, so changes to x in one
 process do not affect the value of x in the other process.


 If both the parent and child processes change the value of x, they are modifying their respective copies of the variable.
 For example, if the parent process changes x to 200, it only affects its own copy of x in its memory.
 Similarly, if the child process changes its copy of x to 300, it does not affect the parent's copy.
 



*/


int main() {
    int x = 100;
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        x = 200;  // Change the value in the child process
        printf("Child - x: %d\n", x);
    } else if (pid > 0) {  // Parent process
        x = 300;  // Change the value in the parent process
        printf("Parent - x: %d\n", x);
    } else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}


