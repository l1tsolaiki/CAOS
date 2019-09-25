#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>

int main(int argc, char const *argv[]) {
    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        return 1;
    }

    unsigned long long sum = 0;
    struct dirent *entry;
    struct stat buf;

    while ((entry = readdir(dir)) != NULL) {
        char str[PATH_MAX];
        sprintf (str, "%s/%s", argv[1], entry->d_name);
        if (stat(str, &buf) != -1) {
            if (buf.st_uid == getuid()) {
                if (isupper(entry->d_name[0])) {
                    if (S_ISREG(buf.st_mode)) {
                        sum += buf.st_size;
                    }
                }
            }
        }
    }

    if (closedir(dir) == -1) {
        return 1;
    }

    printf("%llu\n", sum);
    return 0;
}
