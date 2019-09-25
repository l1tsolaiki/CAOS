#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    float num;
    double res = 0, last_res;
    const char *last_filename = "";
    const char *filename = "";

    sscanf(argv[1], "%f", &num);
    last_res = num;

    if (argc == 4) {
        filename = argv[2];

        void *handle = dlopen(filename, RTLD_LAZY);
        if (handle != NULL) {
            void *sym = dlsym(handle, argv[3]);
            if (sym != NULL) {
                res = ((float (*)(float)) sym)(last_res);
                dlclose(handle);
            }  else {
                res = num;
            }
        } else {
            res = num;
        }
    } else if (argc > 4) {
        for (size_t i = 2; i < argc; i += 2) {
            filename = argv[i];
            if (!strcmp(filename, "-")) {
                filename = last_filename;
            }

            void *handle = dlopen(filename, RTLD_LAZY);
            if (handle != NULL) {
                void *sym = dlsym(handle, argv[i + 1]);
                if (sym != NULL) {
                    res = ((float (*)(float)) sym)(last_res);
                    last_res = res;
                    last_filename = filename;
                    dlclose(handle);
                }  else {
                    continue;
                }
            } else {
                continue;
            }
        }
    } else if (argc == 2) {
        res = num;
    }

    printf("%.6g\n", res);

    return 0;
}

/*
Программе в аргументах командной строки передаются:

1) Вещественное число x0 типа float
2) Последовательность пар аргументов FILE FUNC (возможно пустая).
FILE задает имя разделяемого объектного модуля (SO-файла),
а FUNC — имя функции в нем. Если указанный файл не может быть открыт
как разделяемый объектный модуль, или указанная функция в нем отсутствует,
такая пара FILE FUNC игнорируется. Иначе каждая функция FUNC принимает
значение типа float и возвращает результат типа float.
Если FILE равен - (знак "минус"), должен использоваться SO-файл предыдущей
пары FILE FUNC. Знак "минус" не может использоваться в первой паре,
но может встречаться несколько раз подряд. Необходимо вычислить значение
выражения FUNCn(...(FUNC1(FUNC0(x0)))) и вывести его на стандартный поток
вывода с использованием форматного преобразование %.6g.

Например, если в командной строке заданы аргументы:

./solution 1.0 libm.so sinf libm.so cosf

На стандартный поток вывода должен быть напечатан результат
вычисления cos(sin(1.0)):

0.666367
*/
