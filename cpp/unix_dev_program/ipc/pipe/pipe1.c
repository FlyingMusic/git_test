#include <stdio.h>
#include <unistd.h>

#define MAXLINE 1024

int main() {
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    if (pipe(fd) < 0) {
        printf("pipe error\n");
    }
    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid > 0) {
        close(fd[0]);
        write(fd[1], "hello word\n", 12);
    } else {
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        printf("%s\n", line);
    }
    return 0;
}
