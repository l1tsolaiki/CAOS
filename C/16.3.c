#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int n, status;
    pid_t pid;

    scanf("%d\n", &n);

    for (int i = 1; i <= n; ++i) {
        printf("%d", i);

        if (i == n) {
            printf("\n");
            break;
        } else {
            printf(" ");
        }

        fflush(stdout);

        if ((pid = fork()) < 0) {
            fprintf(stderr, "fork() failed: %s\n", strerror(errno));
            return 1;
        } else if (pid) {
            wait(&status);
            break;
        }
    }

    return 0;
}
