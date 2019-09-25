#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int mode = 1;

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        mode = 1;
    } else if (signo == SIGUSR2) {
        mode = 2;
    }
}

int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = signal_handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    int val;
    while (scanf("%d", &val) == 1) {
        if (mode == 1) {
            printf("%d\n", -val);
        } else {
            printf("%d\n", val * val);
        }
        fflush(stdout);
    }
}

