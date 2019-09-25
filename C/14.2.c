#include <stdio.h>
#include <sys/stat.h>
#include <dlfcn.h>

int main(int argc, char const *argv[]) {
    double num;
    void *handle = dlopen("/lib/libm.so.6", RTLD_LAZY);

    if (handle != NULL) {
        void *sym = dlsym(handle, argv[1]);
        if (sym != NULL) {
            while (scanf("%le", &num) != EOF) {
                double res = ((double (*)(double)) sym)(num);
                printf("%.10g\n", res);
            }
            dlclose(handle);
        }
    }
    return 0;
}

/*
Программе в аргументах командной строки передается имя функции.
Функция находится в стандартной математической библиотеке Си,
принимает один аргумент типа double и возвращает результат типа double.

На стандартном потоке ввода вводится последовательность вещественных чисел.
На стандартном потоке вывода напечатайте результат вычисления функции от
введенных аргументов. Для вывода используйте форматное преобразование %.10g
функции printf.

Математическая библиотека Си находится в файле /lib/libm.so.6.

Пример для функции sin.

Примеры:
Входные данные:

0.5 0.8

Результат работы:

0.4794255386
0.7173560909
*/
