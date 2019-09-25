#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    pid_t pid1, pid2;
    int fd[2];

    if (pipe(fd) < 0) {
        exit(1);
    }

    if ((pid1 = fork()) < 0) {
        exit(1);
    } else if (!pid1) {
        if (dup2(fd[1], 1) < 0) {
            exit(1);
        }

        close(fd[0]);
        close(fd[1]);
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }

    if ((pid2 = fork()) < 0) {
        exit(1);
    } else if (!pid2) {
        if (dup2(fd[0], 0) < 0) {
            exit(1);
        }

        close(fd[0]);
        close(fd[1]);
        execlp(argv[2], argv[2], NULL);
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
