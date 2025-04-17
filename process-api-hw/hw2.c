#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[]) {
    int file_descriptor = open("hw2.out", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

    int return_count = fork();
    if (return_count < 0) {
        // fork fail
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (return_count == 0) {
        // child (new process)
        printf("child (pid:%d)\n", (int) getpid());
        // access file descriptor
        printf("child fd = %d\n", file_descriptor);
        // write to it
        char *child_str = "jfoaweifhnowuahfoewihouwjifanowihfavwnoia\n";
        write(file_descriptor, child_str, strlen(child_str));
    } else {
        // parent will go here
        printf("parent of %d (pid:%d)\n", return_count, (int) getpid());
        // access file descriptor
        printf("parent fd = %d\n", file_descriptor);
        // write to it
        char *parent_str = "fjaowieh90283hb32fb9hachp9wbhce9w2h89h\n";
        write(file_descriptor, parent_str, strlen(parent_str));
    }

    close(file_descriptor);
    return 0;
}
