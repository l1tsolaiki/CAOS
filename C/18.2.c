#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    pid_t pid1, pid2;
    int fd[2], num;
    long long sum = 0;

    if (pipe(fd) < 0) {
        exit(1);
    }

    if ((pid1 = fork()) < 0) {
        exit(1);
    } else if (!pid1) {
        if ((pid2 = fork()) < 0) {
            exit(1);
        } else if (!pid2) {
            close(fd[1]);

            while (read(fd[0], &num, sizeof(num))) {
                sum += num;
            }
            close(fd[0]);
            printf("%lld\n", sum);
            fflush(stdout);
            _exit(1);
        }
        _exit(1);
    }

    while (scanf("%d", &num) != EOF) {
        write(fd[1], &num, sizeof(num));
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}
