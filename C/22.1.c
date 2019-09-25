#include <stdio.h>
#include <pthread.h>
#include <string.h>

struct Threads
{
    int num;
    pthread_t prev_thread;
};

void* thread_func(void *ptr) {
    struct Threads threads = *((struct Threads*)ptr);

    if (threads.num) {
        pthread_join(threads.prev_thread, NULL);
    }

    printf("%d\n", threads.num);
    fflush(stdout);

    return NULL;
}

int main(int argc, char const *argv[]) {
    struct Threads threads[10];
    pthread_t thread = 0;
    int error;

    for (size_t i = 0; i < 10; ++i) {
        threads[i].num = i;
        threads[i].prev_thread = thread;

        error = pthread_create(&thread, NULL, thread_func, &threads[i]);
        if (error) {
            fprintf(stderr, "pthread_create error: %s\n", strerror(error));
            return 1;
        }
    }

    error = pthread_join(thread, NULL);
    if (error) {
        fprintf(stderr, "pthread_join error: %s\n", strerror(error));
        return 1;
    }

    return 0;
}

/*
Функция main должна создать 10 нитей.
Каждая нить должна напечатать на стандартный поток вывода свой
порядковый номер (целое число от 0 до 9) на отдельной строке.

Функция main должна ждать не более одной нити, то есть не допускается вариант,
когда в цикле функция main создает нить и сразу же дожидается ее завершения.

Нити должны работать в таком порядке, чтобы порядковые номера нитей
всегда выводились в возрастающем порядке. Таким образом, программа всегда
должна выводить:

0
1
2
3
4
5
6
7
8
9

Разрешается использовать только функции pthread_create и pthread_join.
*/
