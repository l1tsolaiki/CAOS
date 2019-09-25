#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int f = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (f < 0) {
        return 1;
    }
    unsigned short num;
    while (scanf("%hu", &num) != EOF) {
        char str[2] = {num >> 8, num};
        if (write(f, str, 2) < 0) {
            return 1;
        };
    }
    close(f);
    return 0;
}
