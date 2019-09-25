#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char const *argv[]) {
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC);
    if (fd < 0) {
        return 1;
    }

    struct stat buf;
    if (fstat(fd, &buf) == -1) {
        return 1;
    }

    int rows = strtol(argv[2], NULL, 10);
    int cols = strtol(argv[3], NULL, 10);

    // int off = lseek(fd, rows * cols * INT_MAX - 1, SEEK_SET);
    // if (off < 0) {
    //     return 1;
    // }

    printf("%d %d\n\n", rows, cols);

    int32_t *mp = (int32_t *) mmap(NULL, INT_MAX, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mp == MAP_FAILED) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }

    // void *mp = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    // if (mp == MAP_FAILED) {
    //     fprintf(stderr, "%s\n", strerror(errno));
    //     return 1;
    // }

    int N = rows;
    int M = cols;
    int a[N][M];
    int number = 1;
    for (int i = 0; i < N/2; ++i) {
        for (int j = i; j < M - i; ++j) {
            if (number <= N * M) {
                a[i][j] = number++;
            }
        }

        for (int y = i + 1; y < N - i - 1; ++y) {
            if (number <= N * M) {
                a[y][M - i - 1] = number++;
            }
        }

        for (int j = i; j < M - i; ++j) {
            if (number <= N * M) {
                a[N - i - 1][M - j - 1] = number ++;
            }
        }

        for (int y = i + 1; y < N - i - 1; ++y) {
            if (number <= N * M) {
                a[N - y - 1][i] = number++;
            }
        }
    }

    int k = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            mp[k] = a[i][j];
            ++k;
        }
    }

    // for (int i = 0; i < 20; ++i) {
    //     mp[i] = i + 1;
    // }


    // for (int i = 0; i < rows; ++i) {
    //     for (int j = 0; j < cols; ++j) {
    //         printf("%d ", mp[i * cols + j]);
    //         // printf("%d ", i * cols + j);
    //     }
    //     printf("\n");
    // }

    msync(mp, INT_MAX, MS_SYNC);
    munmap(mp, INT_MAX);
    close(fd);
    return 0;
}
