#include <stdio.h>
#include <unistd.h>
/*


 There are different variants of exec() because they offer flexibility in how you pass arguments, set environment variables,
 and search for the executable in the system's PATH. Different use cases may require different variants.

*/
int main() {
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        execl("/bin/ls", "ls", NULL);
        printf("Child Process/n");
    } else if (pid > 0) {  // Parent process
        // Parent may wait for the child to finish with wait()
	 printf("Parent Process/n");

    } else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}
