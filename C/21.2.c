#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

// bool prime(unsigned int i) {
//     unsigned int k = 0;
//     for (unsigned int j = 2; j <= sqrt(i); ++j) {
//         if (i % j == 0) {
//             ++k;
//         }
//     }
//     return k == 0;
// }

int main(int argc, char const *argv[]) {
    unsigned int low, high;
    int is_prime;

    scanf("%u %u", &low, &high);

    // for (unsigned int i = low; i < high; ++i) {
    //     if (prime(i)) {
    //         printf("%u\n", i);
    //     }
    // }

    for (unsigned int i = low; i < high; ++i) {
        is_prime = 1;
        for (unsigned int j = 2; j * j <= i; ++j) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            printf("%d\n", i);
        }
    }




    return 0;
}

// void handler(int signo) {
//     _exit(0);
// }
//
// int main(int argc, char const *argv[]) {
//     time_t num1;
//     long num2;
//
//     scanf("%ld %ld", &num1, &num2);
//
//     struct timespec ts;
//     ts.tv_sec = num1;
//     ts.tv_nsec = num2;
//
//     struct timeval tv = {};
//     gettimeofday(&tv, NULL);
//
//     int64_t timeout = (ts.tv_sec - tv.tv_sec) * 1000;
//     timeout += (ts.tv_nsec / 1000000 - tv.tv_usec / 1000);
//
//     if (timeout <= 0) {
//         _exit(0);
//     }
//
//     signal(SIGALRM, handler);
//
//     struct itimerval itv = {};
//     itv.it_value.tv_sec = timeout / 1000;
//     itv.it_value.tv_usec = (timeout % 1000) * 1000;
//     setitimer(ITIMER_REAL, &itv, NULL);
//
//     while (1) {}
//     pause();
//
//     return 0;
// }

/*
На стандартном потоке ввода задаются два 32-битных целах беззнаковых
числа low и high.

Программа должна вычислять простые числа в интервале [low,high).
Каждые 0.1 с виртуального времени программа должна вывести на стандартный
поток вывода последнее на текущей момент найденное простое число.
После истечения 0.8 с виртуального времени после вывода последнего найденного
простого числа программа должна завершить работу с кодом 0.
В момент времени 0 ничего не выводится.

Если программа закончила вычисления ранее 0.8 c, программа должна вывести
на стандартный поток вывода число -1 и завершиться с кодом 0.

Если на момент срабатывания таймера ни одно простое число найдено не было,
выводите 0.

После каждого выводимого числа должен выводиться символ перевода строки.
Не забывайте сбрасывать буфер вывода после вывода каждого числа.

Примечание к примеру: вывод может варьироваться в зависимости от скорости
процессора.

Примеры:

Входные данные:
1 10000000

Результат работы:
361789
613651
822191
1004743
1181309
1356007
1526867
1695289
*/
