#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char const *argv[]) {
    int num = 0;
    char buf[8];
    pid_t pid;

    for (int i = 1; i <= 3; ++i) {
        if ((pid = fork()) < 0) {
            fprintf(stderr, "fork() failed: %s\n", strerror(errno));
            return 1;
        } else if (!pid) {
                // printf("son: %d; ppid: %d %d\n", getpid(), getppid(), i);
                read(0, buf, 8);
                char *tmp = buf;
                while (*tmp) {
                    if (isdigit(*tmp)) {
                        num = strtol(tmp, &tmp, 10);
                    } else {
                        tmp++;
                    }
                }
                printf("%d %d\n", i, num * num);
                exit(i);
        } else {
            int status;
            wait(&status);
        }
    }

    return 0;
}
