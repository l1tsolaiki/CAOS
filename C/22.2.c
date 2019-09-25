#include <stdio.h>
#include <pthread.h>
#include <string.h>

void* thread_func(void *ptr) {
    int num;
    if (scanf("%d", &num) == 1) {
        pthread_t thread = 0;
        int error = pthread_create(&thread, NULL, thread_func, NULL);
        if (error) {
            fprintf(stderr, "pthread_create error: %s\n", strerror(error));
        }

        error = pthread_join(thread, NULL);
        if (error) {
            fprintf(stderr, "pthread_join error: %s\n", strerror(error));
        }

        printf("%d\n", num);
        fflush(stdout);
    }

    return NULL;
}

int main(int argc, char const *argv[]) {
    pthread_t thread = 0;
    int error = pthread_create(&thread, NULL, thread_func, NULL);
    if (error) {
        fprintf(stderr, "pthread_create error: %s\n", strerror(error));
        return 1;
    }

    error = pthread_join(thread, NULL);
    if (error) {
        fprintf(stderr, "pthread_join error: %s\n", strerror(error));
        return 1;
    }

    return 0;
}

/*
На стандартном потоке ввода подается последовательность целых чисел,
представимых типом int. Последовательность заканчивается признаком конца ввода.

На стандартный поток вывода напечатайте введенные числа в обратном порядке.

Каждое число должно считываться в отдельной нити. Каждая нить должна
хранить только одно число.

Разрешается использовать только функции pthread_create и pthread_join.

Считайте, что нужное количество нитей создать можно.

Примеры:

Входные данные:
1
2
3
4

Результат работы:
4
3
2
1
*/
