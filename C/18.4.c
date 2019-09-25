// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <limits.h>
//
// int main(int argc, char const *argv[]) {
//     int score, pid1, pid2, fd1[2], fd2[2], num = 1;
//
//     sscanf(argv[1], "%d", &score);
//
//     if (pipe(fd1) < 0) {
//         exit(1);
//     }
//
//     if (pipe(fd2) < 0) {
//         exit(1);
//     }
//
//     write(fd1[1], &num, sizeof(num));
//
//     if ((pid1 = fork()) < 0) {
//         exit(1);
//     } else if (!pid1) {
//         if (num == score - 1) {
//             printf("%d %d\n", 1, num);
//             fflush(stdout);
//         }
//         while (num < score - 1) {
//             read(fd1[0], &num, sizeof(num));
//             printf("%d %d\n", 1, num);
//             fflush(stdout);
//             ++num;
//             if (write(fd2[1], &num, sizeof(num)) > PIPE_BUF) {
//                 _exit(1);
//             }
//         }
//         _exit(1);
//     }
//
//     if ((pid2 = fork()) < 0) {
//         exit(1);
//     } else if (!pid2) {
//         while (num < score - 1) {
//             read(fd2[0], &num, sizeof(num));
//             printf("%d %d\n", 2, num);
//             fflush(stdout);
//             ++num;
//             if (write(fd1[1], &num, sizeof(num)) > PIPE_BUF) {
//                 _exit(1);
//             }
//         }
//         _exit(1);
//     }
//
//     wait(NULL);
//     wait(NULL);
//     printf("Done\n");
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char const *argv[]) {
    int score, fd1[2], fd2[2], num = 1;
    pid_t pid1, pid2;
    FILE *mf[2][2];

    sscanf(argv[1], "%d", &score);

    if (pipe(fd1) < 0) {
        exit(1);
    }

    if (pipe(fd2) < 0) {
        exit(1);
    }

    // mf1 = fdopen(fd1, "r+");
    // mf2 = fdopen(fd2, "r+");

    if (dup2(fd[1], 1) < 0) {
        exit(1);
    }

    write(fd1[1], &num, sizeof(num));

    if ((pid1 = fork()) < 0) {
        exit(1);
    } else if (!pid1) {
        if (num == score - 1) {
            printf("%d %d\n", 1, num);
            fflush(stdout);
        }
        while (num < score - 1) {
            read(fd1[0], &num, sizeof(num));
            printf("%d %d\n", 1, num);
            fflush(stdout);
            ++num;
            if (write(fd2[1], &num, sizeof(num)) > PIPE_BUF) {
                _exit(1);
            }
        }
        _exit(1);
    }

    if ((pid2 = fork()) < 0) {
        exit(1);
    } else if (!pid2) {
        while (num < score - 1) {
            read(fd2[0], &num, sizeof(num));
            printf("%d %d\n", 2, num);
            fflush(stdout);
            ++num;
            if (write(fd1[1], &num, sizeof(num)) > PIPE_BUF) {
                _exit(1);
            }
        }
        _exit(1);
    }

    wait(NULL);
    wait(NULL);
    printf("Done\n");
    return 0;
}
