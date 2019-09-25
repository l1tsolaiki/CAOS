#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* thread_func(void *ptr) {
    int num;
    long long* sum = malloc(sizeof(long long));
    if (sum == NULL) {
        exit(1);
    }
    *sum = 0;

    while (scanf("%d", &num) == 1) {
        *sum += num;
        sched_yield();
    }

    return sum;
}

int main(int argc, char const *argv[]) {
    int error, N = strtol(argv[1], NULL, 10);
    long long sum = 0;

    pthread_t *threads = malloc(N * sizeof(pthread_t));
    if (threads == NULL) {
        return 1;
    }

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));

    for (size_t i = 0; i < N; ++i) {
        error = pthread_create(&threads[i], &attr, thread_func, NULL);
        if (error) {
            fprintf(stderr, "pthread_create error: %s\n", strerror(error));
            return 1;
        }
    }

    for (size_t i = 0; i < N; ++i) {
        long long *tmp;

        error = pthread_join(threads[i], (void**)&tmp);
        if (error) {
            fprintf(stderr, "pthread_join error: %s\n", strerror(error));
            return 1;
        }

        sum += *tmp;
        free(tmp);
    }


    printf("%lld\n", sum);
    pthread_attr_destroy(&attr);
    free(threads);

    return 0;
}
