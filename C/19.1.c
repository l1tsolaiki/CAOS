#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile int flag = 0;
int count = 0;

void sigint_handler(int signo) {
    if (count == 4) {
        flag = 1;
        _exit(0);
    }

    printf("%d\n", count);
    fflush(stdout);
    ++count;
}

int main(int argc, char const *argv[]) {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    printf("%d\n", getpid());
    fflush(stdout);

    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    while (!flag) {
        sigsuspend(&oldmask);
    }
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    return 0;
}

/*
Программа должна напечатать на стандартный поток вывода свой PID,
после чего перейти в режим ожидания сигналов. Программа должна обрабатывать
сигнал SIGINT. На каждый приход сигнала программа должна напечатать номер
поступления сигнала (0, 1, 2) — каждый раз на отдельной строке. На пятый
приход сигнала программа не должна ничего выводить, а просто завершиться
с кодом завершения 0.

Таким образом, программа всегда должна выводить:

СВОЙ-PID
0
1
2
3

Стандартный ввод и стандартный вывод программы будут перенаправлены.
Не забывайте выводить разделитель и сбрасывать буфер вывода.
С другой стороны каналов находится другой процесс, который начнет свою
работу как только получит pid процесса.

Не используйте активное ожидание сигнала.

Вывод на стандартный поток вывода разместите в обработчике сигнала.

Вариант семантики сигналов (SysV или BSD), используемый функцией signal,
неизвестен.
*/
