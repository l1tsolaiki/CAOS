#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile int flag = 0;

void sigint_handler(int signo) {
    if (signo == SIGTERM) {
        flag = 0;
    } else if (signo == SIGUSR1) {
        flag = 1;
    } else if (signo == SIGUSR2) {
        flag = 2;
    }
}

int main(int argc, char const *argv[]) {
    int sigusr1_count = 0, sigusr2_count = 0;
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigaddset(&mask, SIGTERM);

    printf("%d\n", getpid());
    fflush(stdout);

    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    while (1) {
        sigsuspend(&oldmask);
        if (flag == 1) {
            printf("%d %d\n", sigusr1_count, sigusr2_count);
            fflush(stdout);
            ++sigusr1_count;
        } else if (flag == 2) {
            ++sigusr2_count;
        } else if (!flag) {
            _exit(0);
        }
    }
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    return 0;
}

/*
Программа должна напечатать на стандартный поток вывода свой PID
и перейти в режим ожидания поступления сигналов.

При поступлении сигнала SIGUSR2 программа должна увеличивать
счетчик поступления сигнала SIGUSR2.

При поступлении сигнала SIGUSR1 программа должна вывести на стандартный
поток вывода счетчик поступлений сигнала SIGUSR1 и счетчик поступления
сигнала SIGUSR2, затем увеличить счетчик поступления сигнала SIGUSR1.

При поступлении сигнала SIGTERM программа не должна ничего выводить и
должна завершить работу с кодом завершения 0.

Обработчики сигналов должны не выполнять никаких действий, кроме изменения
значений глобальных переменных. Ожидание поступления сигналов выполняйте
с помощью sigsuspend.

Стандартный поток вывода вашей программы будет перенаправлен в канал.
Не забывайте выводить разделитель после вывода чисел и сбрасывать буфер вывода.
*/
