#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int check_execlp(const char *cmd) {
    int pid, status;

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
    if (check_execlp(argv[1])) {
        if (!check_execlp(argv[2])) {
            if (!check_execlp(argv[3])) {
                return 0;
            } else {
                return 1;
            }
        } else {
            return 1;
        }
    } else {
        if (!check_execlp(argv[3])) {
            return 0;
        } else {
            return 1;
        }
    }

    return 1;
}
