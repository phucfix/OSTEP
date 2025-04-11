#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    // The process calls the fork() system
    // call, which the OS provides as a way to create a new process
    // The odd part: the process that is created is an (almost) exact copy of the calling pro-
    // cess. That means that to the OS, it now looks like there are two copies of
    // the program p1 running and both are about to return from the fork() system call.
    int rc = fork();
    if (rc < 0) {
        // fork fail
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("p3.c"); // arg: input file
        myargs[2] = NULL;
        execvp(myargs[0], myargs);
        printf("this shouldn’t print out");
    } else {
       int rc_wait = wait(NULL);
       printf("parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    }
    return 0;
}
