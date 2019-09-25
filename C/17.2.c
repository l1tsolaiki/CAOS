#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int mysys(const char *str) {
    int pid, status;

    if ((pid = fork()) < 0) {
        return -1;
    } else if (!pid) {
        execl("/bin/sh", "/bin/sh", "-c", str, NULL);
        _exit(127);
    }

    wait(&status);

    if (WIFEXITED(status)) {
        if (WIFSIGNALED(status)) {
            return WTERMSIG(status) + 128;
        }
        return WEXITSTATUS(status);
    }
    return -1;
}
