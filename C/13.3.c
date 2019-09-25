#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    FILE *fp;
    int year, month, day, hour, minute, second;
    struct tm* time_check1;
    struct tm* time_check2;
    time_t rawtime;
    time(&rawtime);

    if ((fp = fopen(argv[1], "r")) != NULL) {
        fscanf(fp, "%d/%d/%d%d:%d:%d",
            &year, &month, &day, &hour, &minute, &second);

        time_check1 = localtime(&rawtime);
        time_check1->tm_year = year - 1900;
        time_check1->tm_mon = month - 1;
        time_check1->tm_mday = day;
        time_check1->tm_hour = hour;
        time_check1->tm_min = minute;
        time_check1->tm_sec = second;
        time_check1->tm_isdst = -1;
        time_t sec1 = mktime(time_check1);
        if (sec1 != -1) {

            while (fscanf(fp, "%d/%d/%d%d:%d:%d",
                &year, &month, &day, &hour, &minute, &second) != EOF) {
                time_check2 = localtime(&rawtime);
                time_check2->tm_year = year - 1900;
                time_check2->tm_mon = month - 1;
                time_check2->tm_mday = day;
                time_check2->tm_hour = hour;
                time_check2->tm_min = minute;
                time_check2->tm_sec = second;
                time_check2->tm_isdst = -1;
                time_t sec2 = mktime(time_check2);
                if (sec2 != -1) {
                    printf("%ld\n", sec2 - sec1);
                    sec1 = sec2;
                }
            }
        }
    }
    return 0;
}
