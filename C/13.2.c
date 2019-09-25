#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    unsigned long long sum = 0;
    struct stat buf;

    for(int i = 1; i < argc; ++i) {
        if (lstat(argv[i], &buf) != -1) {
            if (access(argv[i], F_OK) == 0) {
                if (S_ISREG(buf.st_mode) && !S_ISLNK(buf.st_mode)) {
                    if (buf.st_nlink == 1) {
                        sum += buf.st_size;
                    }
                }
            }
        }
    }
    printf("%llu\n", sum);
    return 0;
}
