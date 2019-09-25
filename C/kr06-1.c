#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    int year, month, count = 0;
    struct tm* time_check;
    time_t rawtime;

    year = strtol(argv[1], NULL, 10);
    month = strtol(argv[2], NULL, 10);

    time_check = localtime(&rawtime);
    time_check->tm_year = year - 1900;
    time_check->tm_mon = month - 1;
    time_check->tm_mday = 1;

    rawtime = mktime(time_check);

    while (time_check->tm_mon == month - 1) {
        if (1 <= time_check->tm_wday && time_check->tm_wday <= 4) {
            count += 8;
        } else if (time_check->tm_wday == 5) {
            count += 6;
        }
        rawtime += 86400;
        time_check = localtime(&rawtime);
        rawtime = mktime(time_check);
    }
    printf("%d\n", count);

    return 0;
}
