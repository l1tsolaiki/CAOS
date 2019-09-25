#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

struct Args
{
    uint64_t args_base;
    int args_count;
};

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
bool need_increment = false;

void* thread_func(void *ptr) {
    struct Args arg = *((struct Args*)ptr);

    arg.args_base += 10;
    arg.args_count += 10;

    pthread_mutex_lock(&mutex);
    need_increment = true;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char const *argv[]) {
    uint64_t base;
    int count;

    scanf("%lld %d\n", &base, &count);

    struct Args arg;
    arg.args_base = base;
    arg.args_count = count;

    pthread_t thread = 0;
    int error;

    error = pthread_create(&thread, NULL, thread_func,  &arg);
    if (error) {
        fprintf(stderr, "pthread_create error: %s\n", strerror(error));
        return 1;
    }

    pthread_mutex_lock(&mutex);
    if (!need_increment) {
        pthread_cond_wait(&cond, &mutex);
    }

    pthread_mutex_unlock(&mutex);


    printf("%lld %d\n", arg.args_base, arg.args_count);


    error = pthread_join(thread, NULL);
    if (error) {
        fprintf(stderr, "pthread_join error: %s\n", strerror(error));
        return 1;
    }

    pthread_cond_destroy(&cond);

    // pthread_t threads[THREADS_COUNT];
    // int error;
    //
    // for (size_t i = 0; i < THREADS_COUNT; ++i) {
    //     error = pthread_create(&threads[i], NULL, thread_func,
    //         (void*) (intptr_t) i);
    //     if (error) {
    //         fprintf(stderr, "pthread_create error: %s\n", strerror(error));
    //         return 1;
    //     }
    // }
    //
    // for (size_t i = 0; i < THREADS_COUNT; ++i) {
    //     error = pthread_join(threads[i], NULL);
    //     if (error) {
    //         fprintf(stderr, "pthread_join error: %s\n", strerror(error));
    //         return 1;
    //     }
    // }
    //
    // for (size_t i = 0; i < THREADS_COUNT; ++i) {
    //     printf("%.10g\n", data[i]);
    // }

    return 0;
}
