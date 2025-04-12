#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    int x = 100;

    int rc = fork();
    if (rc < 0) {
        // fork fail
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("child (pid:%d): x = %d\n", (int) getpid(), x);
        printf("Hello\n");
    } else {
        sleep(1);
        printf("Goodbye\n");
        printf("parent of %d (pid:%d): x = %d\n", rc, (int) getpid(), x);
    }

    return 0;
}
