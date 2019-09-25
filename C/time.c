#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int main() {
    printf("time %ld\n", time(NULL));   //Текущее время
    struct timeval tp;
    gettimeofday(&tp, NULL);    //Текущее время (более точно)
    printf("time: seconds = %ld, microseconds = %d\n", tp.tv_sec, tp.tv_usec);

    time_t now = time(NULL);    //Текущее время
    struct tm* utc = gmtime(&now);
    struct tm* local = localtime(&now);
    printf("utc: %d, local: %d\n", utc->tm_hour, local->tm_hour);

    printf("time %ld\n", mktime(local));

    printf("%s", asctime(local));
    printf("%s", ctime(&now));

    char str[20];
    strftime(str, 20, "%H:%M\n", local);
    printf("%s", str);

    return 0;
}
/*
time 1551969242
time: seconds = 1551969242, microseconds = 173365
utc: 14, local: 17
time 1551969242
Thu Mar  7 17:34:02 2019
Thu Mar  7 17:34:02 2019
17:34

// Добавление нескольких дней к текущему времени
  char s1[40] = { 0 }, s2[40] = { 0 };

  const time_t timer = time(NULL);
  struct tm *local = localtime(&timer);

  strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", local);
  printf("%s\n", s1);

  local->tm_mday += ADD_DAYS;
  time_t next = mktime(local);
  local = localtime(&next);
  strftime(s2, 80, "%d.%m.%Y %H:%M:%S ", local);
  printf("%s\n", s2);
*/
