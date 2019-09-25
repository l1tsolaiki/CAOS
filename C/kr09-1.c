#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

enum { N = 5 };

pthread_t ids[N];
pthread_t ids2[N];

void *func2(void *arg)
{
    pause();
    return NULL;
}

void *func(void *arg)
{
    int serial = (int) (intptr_t) arg;

    if (serial == 0) {
        pthread_join(ids2[2], NULL);
    } else if (serial == 1) {
        pthread_join(ids2[0], NULL);
    } else if (serial == 2) {
        pthread_join(ids2[3], NULL);
    } else if (serial == 3) {
        pthread_join(ids2[4], NULL);
    } else if (serial == 4) {
        pthread_join(ids2[1], NULL);
    }

    printf("%d\n", serial);
    fflush(stdout);

    return NULL;
}

int main()
{
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids2[i], NULL, func2, NULL);
    }
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids[i], NULL, func, (void*) (intptr_t) i);
    }
    for (int i = 0; i < N; ++i) {
        pthread_cancel(ids2[i]);
    }

    pthread_join(ids[4], NULL);
    return 0;
}
