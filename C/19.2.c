#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile int flag = 1;

void sigint_handler(int signo) {
    if (signo == SIGUSR1) {
        flag = 1;
    } else if (signo == SIGUSR2) {
        flag = 0;
    }
}

int main(int argc, char const *argv[]) {
    int num;
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    while (scanf("%d", &num) > 0) {
        if (flag) {
            printf("%d\n", -num);
            fflush(stdout);
        } else {
            printf("%d\n", num * num);
            fflush(stdout);
        }
    }

    return 0;
}

/*
Программа должна напечатать на стандартный поток вывода свой pid.

Затем программе на стандартном потоке ввода подаются целые числа.
В зависимости от режима работы для каждого введенного числа на стандартный
поток вывода программа выводит либо число, взятое с обратным знаком,
либо квадрат числа.

При получении сигнала SIGUSR1 программа переключается в режим взятия
обратного знака числа. При получении сигнала SIGUSR2 программа переключается
в режим возвведения числа в квадрат.

Стандартный ввод и стандартный вывод программы будут перенаправлены.
Не забывайте сбрасывать буфер вывода. С другой стороны каналов находится
другой процесс, который начнет свою работу как только получит pid процесса.

По умолчанию программа работает в режиме взятия обратного знака числа.
*/
