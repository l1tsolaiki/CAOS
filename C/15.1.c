#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }

    struct stat buf;
    if (fstat(fd, &buf) == -1) {
        return 1;
    }

    void *mp = mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (mp == MAP_FAILED) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }

    long double sum = 0;
    int count = 0;

    double *data = mp;
    for (int i = 0; i < buf.st_size / sizeof(double); ++i) {
        sum += data[i];
        ++count;
    }

    printf("%a\n", (double) sum / count);
    munmap(mp, buf.st_size);
    close(fd);
    return 0;
}
