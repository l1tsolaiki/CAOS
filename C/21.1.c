#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int signo) {
    _exit(0);
}

int main(int argc, char const *argv[]) {
    time_t num1;
    long num2;

    scanf("%ld %ld", &num1, &num2);

    struct timespec ts;
    ts.tv_sec = num1;
    ts.tv_nsec = num2;

    struct timeval tv = {};
    gettimeofday(&tv, NULL);

    int64_t timeout = (ts.tv_sec - tv.tv_sec) * 1000;
    timeout += (ts.tv_nsec / 1000000 - tv.tv_usec / 1000);

    if (timeout <= 0) {
        _exit(0);
    }

    signal(SIGALRM, handler);

    struct itimerval itv = {};
    itv.it_value.tv_sec = timeout / 1000;
    itv.it_value.tv_usec = (timeout % 1000) * 1000;
    setitimer(ITIMER_REAL, &itv, NULL);

    while (1) {}
    pause();

    return 0;
}

/*
На стандартном потоке ввода программе задаются два целых числа.
Первое число представимо типом time_t, второе число - 32-битное целое в
интервале от 0 до 999999999. Эти числа в совокупности задают значение
типа struct timespec, определяющие момент времени наступления события.
Программа должна с помощью системного вызова setitimer настроить таймер
реального времени, чтобы он сработал в момент времени наступления события.
Программа дожидается наступления события и завершает свою работу с кодом 0.

Если момент наступления события оказался в прошлом, программа должна
завершиться немедленно.
*/
