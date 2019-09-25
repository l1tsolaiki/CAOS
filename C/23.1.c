#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

enum { THREADS_COUNT = 3, TASK_COUNT = 1000000 };

double data[THREADS_COUNT];

void* thread_func(void *ptr) {
    int num = (int) (intptr_t) ptr;
    for (size_t i = 0; i < TASK_COUNT; ++i) {
        if (pthread_mutex_lock(&mutex)) {
            exit(1);
        }

        data[num] += (num + 1) * 100;
        data[(num + 1) % THREADS_COUNT] -= (num + 1) * 100 + 1;

        if (pthread_mutex_unlock(&mutex)) {
            exit(1);
        }
    }

    return NULL;
}

int main(int argc, char const *argv[]) {
    pthread_t threads[THREADS_COUNT];
    int error;

    for (size_t i = 0; i < THREADS_COUNT; ++i) {
        error = pthread_create(&threads[i], NULL, thread_func,
            (void*) (intptr_t) i);
        if (error) {
            fprintf(stderr, "pthread_create error: %s\n", strerror(error));
            return 1;
        }
    }

    for (size_t i = 0; i < THREADS_COUNT; ++i) {
        error = pthread_join(threads[i], NULL);
        if (error) {
            fprintf(stderr, "pthread_join error: %s\n", strerror(error));
            return 1;
        }
    }

    for (size_t i = 0; i < THREADS_COUNT; ++i) {
        printf("%.10g\n", data[i]);
    }

    return 0;
}

/*
Программа должна создать три нити, пронумерованные от 0 до 2.
Нити работают над общим глобальным массивом типа double из трех элементов.
Каждая нить 1000000 раз выполняет следующие операции:

Нить 0 прибавляет к элементу [0] число 100 и вычитает из элемента [1] число 101.
Нить 1 прибавляет к элементу [1] число 200 и вычитает из элемента [2] число 201.
Нить 2 прибавляет к элементу [2] число 300 и вычитает из элемента [0] число 301.

Программа дожидается завершения всех нитей и выводит на стандартный поток вывода
значения элементов массива.
Для вывода используйте форматное преобразование %.10g.

Для обеспечения корректной работы используйте один мьютекс.
Сравните результат работы с результатом работы без использования мьютексов.

Используйте одну функцию нити для всех трех нитей.
В программе объявите константу со значением 3 и константу со
значением 1000000 и используйте их.
*/
