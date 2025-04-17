#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int pipefd[2]; // pipefd[0] to read, pipefd[1] to write
    
    // Create pipe
    if (pipe(pipefd) == -1) {
        fprintf(stderr, "pipe create failed\n");
        exit(1);
    }

    int pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (pid1 == 0) {
        // Write to pipe
        close(pipefd[0]); // close read head

        // change stdout to write head of pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // write to stdout, now is pipe
        printf("Hello from 1\n");
        exit(0);
    }

    int pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (pid2 == 0) {
        // read from pipe
        close(pipefd[1]); // close write pipe, dont' neccessary

        // change stdion to read head of pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);   // close because changed
        
        // Write from pip
        char buf[50];
        fgets(buf, 50, stdin);
        printf("Child 2 receive: %s\n", buf);
        exit(0); 
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    printf("Finished\n");

    return 0;
}
