#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    int num, tmp;

    while (scanf("%d\n", &num) != EOF) {
        time_t now = time(NULL);
        if (__builtin_mul_overflow(86400, num, &tmp)) {
            printf("%s\n", "OVERFLOW");
        } else {
            if (__builtin_add_overflow(now, tmp, &now)) {
                printf("%s\n", "OVERFLOW");
            } else {
                if (now != -1) {
                    struct tm* local = localtime(&now);
                    char buf[20];
                    strftime(buf, 20, "%F", local);
                    printf("%s\n", buf);
                } else {
                    printf("%s\n", "OVERFLOW");
                }
            }
        }
    }
    return 0;
}
