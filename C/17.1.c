#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int fd_in, fd_out, pid;

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork() failed: %s\n", strerror(errno));
        return 1;
    } else if (!pid) {
        fd_in = open(argv[2], O_RDONLY);
        if (fd_in < 0) {
            return 1;
        }

        if (dup2(fd_in, 0) < 0) {
            fprintf(stderr, "dup2(fd_in, 0) failed: %s\n", strerror(errno));
            return 1;
        }

        close(fd_in);

        fd_out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd_out < 0) {
            return 1;
        }

        if (dup2(fd_out, 1) < 0) {
            fprintf(stderr, "dup2(fd_out, 1) failed: %s\n", strerror(errno));
            return 1;
        }

        close(fd_out);

        execlp(argv[1], argv[1], NULL);
        fprintf(stderr, "execlp() failed: %s\n", strerror(errno));
        _exit(1);
    } else {
        wait(NULL);
    }

    return 0;
}

/*
В аргументах командной строки передаются параметры CMD FILE1 FILE2.
Реализуйте запуск процесса CMD с перенаправлением стандартных потоков
как в команде:

CMD < FILE1 > FILE2
Файл FILE2 должен создаваться с помощью системного вызова open с
правами чтение-запись для всех категорий пользователей
(владелец, группа, прочие).
Если файл уже существует, его права доступа не изменяются.

Для запуска файла на выполнение используйте execlp.
Не используйте umask для изменения соответствующего параметра процесса.

Процесс-родитель должен завершаться самым последним из всех процессов.
Процесс-родитель всегда завершается с кодом 0.

Например, при запуске вашей программы:

  ./prog wc in.txt out.txt
В отдельном процессе должна быть запущена программа wc,
ее стандартный ввод должен быть перенаправлен на чтение из файла in.txt,
а стандартный вывод - на запись в файл out.txt.
*/
