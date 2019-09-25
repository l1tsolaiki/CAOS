#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

static int cmp(const void *a, const void *b) {
    return strcmp(* (char * const *) a, * (char * const *) b);
}

void recursive(char *path, char *dname) {
    struct stat buf;
    struct dirent *dirp;
    DIR *dp;
    char new_path[PATH_MAX];

    if (lstat(path, &buf) != -1 && S_ISDIR(buf.st_mode)) {
        if ((dp = opendir(path)) != NULL) {
            printf("%s %s\n", "cd", dname);

            int N = 10000, i = 0;
            char *array[N];

            while ((dirp = readdir(dp)) != NULL) {
                if (strcmp(dirp->d_name, ".") == 0 ||
                    strcmp(dirp->d_name, "..") == 0) {
                    continue;
                }

                array[i] = malloc(strlen(dirp->d_name) + 1);
                strcpy(array[i], dirp->d_name);
                ++i;
            }

            qsort(array, i, sizeof(char *), cmp);

            for (int j = 0; j < i; ++j) {
                sprintf(new_path, "%s/%s", path, array[j]);
                recursive(new_path, array[j]);
            }

            printf("%s\n", "cd ..");
            if (closedir(dp) == -1) {
                fprintf(stderr, "unable to close the directory %s: %s\n",
                path, strerror(errno));
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    char *fullpath;
    fullpath = malloc(PATH_MAX + 1);

    if (fullpath == NULL) {
        fprintf(stderr, "unable to allocate memory: %s\n", strerror(errno));
        fflush(NULL);
        abort();
    }

    strncpy(fullpath, argv[1], PATH_MAX + 1);
    fullpath[PATH_MAX] = 0;

    char *istr = malloc(strlen(fullpath) + 1);
    int j = 0;

    for (int i = 0; i < strlen(fullpath); ++i) {
        if (fullpath[i] == '/') {
            j = i;
        }
    }

    strcpy(istr, &fullpath[j + 1]);
    recursive(fullpath, istr);
    return 0;
}
