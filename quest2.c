#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/*
 When a program opens a file using the open() system call and then calls fork() to create a new process,
 both the parent and child processes can access the file descriptor returned by open().
 However,when both the prcoesses write concurrently to the file, it can lead to issues like data corruption or interleaved
 content. This is because the order in which data is written is not guaranteed, as it depends on the operating system's
 scheduling. To avoid such problems, synchronization mechanisms like locks or inter-process communication should be used
 to coordinate access to the shared file, ensuring that only one process writes to it at a time, thus maintaining data
 integrity.
*/
int main() {
    int fd = open("example.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        dprintf(fd, "Child: Writing to the file\n");
    } else if (pid > 0) {  // Parent process
        dprintf(fd, "Parent: Writing to the file\n");
    } else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    close(fd);
    return 0;
}
