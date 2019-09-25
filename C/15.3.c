#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int fd, count, checker = 0;
    struct stat buf;
    void *mp;

    for (int i = 1; i < argc; ++i) {
        fd = open(argv[i], O_RDONLY);
        if (fd > 0 && fstat(fd, &buf) != -1) {
            if (access(argv[i], F_OK) == 0) {
                if (buf.st_size != 0) {
                    mp = mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, fd, 0);
                    if (mp != MAP_FAILED) {
                        count = 0;
                        char *data = mp;

                        for (int i = 0; i < buf.st_size / sizeof(char); ++i) {
                            checker = 1;
                            if (data[i] == '\n') {
                                ++count;
                                checker = 0;
                            }
                        }

                        if (checker) {
                            ++count;
                        }

                        printf("%d\n", count);
                        munmap(mp, buf.st_size);
                        close(fd);
                    } else {
                        printf("%d\n", -1);
                    }
                } else {
                    printf("%d\n", 0);
                }
            } else {
                printf("%d\n", -1);
            }
        } else {
            printf("%d\n", -1);
        }
    }
    return 0;
}
