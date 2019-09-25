#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>

volatile int usr_num;
volatile int mode = 0;  // Режим выделения номера сети
volatile int flag = 0;
int count = 0;

unsigned int IPv4_address(unsigned int num) {
    unsigned int x, t, res = 0;

    x = num / pow(8, 8);
    if (191 <= x || x <= 128) {
        return res;
    }

    if (mode) {
        t = 2 << 15;
        x = num % t;
        res = x;
    } else {
        t = 2 << 29;
        x = num % t;
        x = x / (2 << 15);
        res = x;
    }

    return res;
}

void sigint_handler(int signo) {
    if (signo == SIGUSR1) {
        usr_num = 1;
        ++count;
    } else if (signo == SIGUSR2) {
        usr_num = 2;
    }

    if (count == 5) {
        flag = 1;
        _exit(0);
    }
}

int main(int argc, char const *argv[]) {
    unsigned int num;

    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);

    printf("%d\n", getpid());
    fflush(stdout);

    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    while (!flag) {
        sigsuspend(&oldmask);
        if (usr_num == 1) {
            if (mode) {
                mode = 0;
            } else {
                mode = 1;
            }
        } else if (usr_num == 2) {
            scanf("%o", &num);
            printf("%u\n", IPv4_address(num));
            fflush(stdout);
        }
    }
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    return 0;
}

/*
Программа должна напечатать на стандартный поток вывода свой идентификатор
процесса. Это означает готовность программы к обработке последующих данных.

Программа должна выполнять обработку входных данных в одном из двух режимов:
режим выделения номера сети из адреса IPv4 и режим выделения номера хоста
из адреса IPv4. В начале работы программы установлен режим выделения
номера сети. Программа должна обрабатывать только IP-адреса класса B.

"Классовая организация"

По приходу сигнала USR1 программа переключается между этими режимами.
По приходу сигнала USR2 программа должна считать со стандартного потока
ввода 32-битное целое беззнаковое число, записанное в восьмеричном
представлении, выделить из него соответствующую компоненту и вывести
ее на стандартный поток вывода в десятичном представлении.

Если поданное на вход программе число не является адресом класса B
на стандартный поток вывода напечатайте 0.

Программа должна завершить работу с кодом 0 при приходе сигнала USR1
в пятый (считая от 1) раз.

Стандартный ввод и стандартный вывод программы будут перенаправлены в каналы.
Не забывайте сбрасывать буфер вывода. С другой стороны каналов находится
другой процесс, который начнет свою работу как только получит pid процесса.

Например, при последовательности действий:

(USR2)
20703646065
(USR2)
34040000261
(USR1)
(USR2)
23027032622
(USR1)
(USR2)
24445767741
(USR1)
(USR1)
(USR1)
Должен быть получен результат:

1807
0
13714
9367
*/
