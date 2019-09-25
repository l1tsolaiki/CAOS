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
    pid_t pid, ppid = getpid();

    while (scanf("%d", &n) != EOF) {
        if ((pid = fork()) < 0) {
            // fprintf(stderr, "fork() failed: %s\n", strerror(errno));
            if (getpid() == ppid) {
                printf("-1\n");
                return 0;
            }
            return 1;
        } else if (pid) {   //parent
            wait(&status);
            if (!status) {
                printf("%d\n", n);
                return 0;
            } else {
                if (getpid() == ppid) {
                    printf("-1\n");
                    return 0;
                }
                return 1;
            }
            break;
        }
    }

    return 0;
}
