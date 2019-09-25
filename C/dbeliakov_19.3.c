#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int sig_type = 0;

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        sig_type = 1;
    } else if (signo == SIGUSR2) {
        sig_type = 2;
    } else if (signo == SIGTERM) {
        sig_type = 3;
    }
}

int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = signal_handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigaddset(&mask, SIGTERM);

    sigprocmask(SIG_BLOCK, &mask, &oldmask);

    printf("%d\n", getpid());
    fflush(stdout);

    int cnt1 = 0;
    int cnt2 = 0;
    while (1) {
        while(sig_type == 0) {
            sigsuspend(&oldmask);
        }
        if (sig_type == 1) {
            printf("%d %d\n", cnt1, cnt2);
            ++cnt1;
        } else if (sig_type == 2) {
            ++cnt2;
        } else if (sig_type == 3) {
            _exit(0);
        }
        fflush(stdout);
        sig_type = 0;
    }
}

