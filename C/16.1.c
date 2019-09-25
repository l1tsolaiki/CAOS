#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int status;
    pid_t pid, pid2, pid3, ppid2, ppid3, p2, p3;

    if ((p2 = fork()) < 0) {
        fprintf(stderr, "fork() failed: %s\n", strerror(errno));
        return 1;
    } else if (!p2) {   //son
        pid2 = getpid();
        ppid2 = getppid();
        // printf("son: %d; parent: %d\n", pid2, ppid2);

        if ((p3 = fork()) < 0) {
            fprintf(stderr, "fork() failed: %s\n", strerror(errno));
            return 1;
        } else if (!p3) {   //grandson
            pid3 = getpid();
            ppid3 = getppid();
            // printf("grandson: %d; son: %d\n", pid3, ppid3);
            exit(3);
        } else {    //parent
            if ((pid = wait(&status))) {
                // printf("%d завершился с кодом: %d\n", pid, WEXITSTATUS(status));
                printf("3 ");
            }
        }
        exit(2);
    } else {    //parent
        if ((pid = wait(&status))) {
            // printf("%d завершился с кодом: %d\n", pid, WEXITSTATUS(status));
            printf("2 ");
        }
    }

    printf("1\n");
    return 0;
}
