#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int check_execlp(const char *cmd) {
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        return -1;
    } else if (!pid) {
        execlp("/bin/sh", "/bin/sh", "-c", cmd, NULL);
        exit(1);
    }

    wait(&status);

    if (WIFEXITED(status)) {
        if (!WEXITSTATUS(status)) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char const *argv[]) {
    int fd, pfd[2];

    fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        return 1;
    }



    return 0;
}
