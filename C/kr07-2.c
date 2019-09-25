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
    int fd_in, fd_out = 0, fd_err, pid;

    if ((pid = fork()) < 0) {
        perror("fork()");
        return 42;
    } else if (!pid) {
        fd_err = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd_err < 0) {
            return 42;
        }

        if (dup2(fd_err, 2) < 0) {
            perror("dup2(fd_err, 2)");
            return 42;
        }

        close(fd_err);

        fd_in = open(argv[2], O_RDONLY);
        if (fd_in < 0) {
            return 42;
        }

        if (dup2(fd_in, 0) < 0) {
            perror("dup2(fd_in, 2)");
            return 42;
        }

        close(fd_in);

        fd_out = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (fd_out < 0) {
            return 42;
        }

        if (dup2(fd_out, 1) < 0) {
            perror("dup2(fd_out, 2)");
            return 42;
        }

        close(fd_out);

        execlp(argv[1], argv[1], NULL);
        perror("execlp");
        _exit(42);
    } else {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            fprintf(stdout, "%d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}

/*
В аргументах командной строки передаются параметры CMD FILE1 FILE2 FILE3.
Реализуйте запуск процесса CMD с перенаправлением стандартных потоков
как в команде:

CMD < FILE1 >> FILE2 2> FILE3
Файлы FILE2, FILE3 должны создаваться с помощью системного вызова open с
правами чтение-запись для владельца и группы. Если файл уже существует,
его права доступа не изменяются.

Если в созданном в рамках вашей программы
процессе-сыне какой-либо системный вызов завершился с ошибкой,
этот процесс должен завершиться с кодом 42.

После завершения созданного процесса родитель должен напечатать на
стандартный поток вывода целое число - статус завершения процесса,
заполненное в результате системного вызова wait без каких-либо модификаций.

Процесс-родитель должен завершаться самым последним из всех процессов.
Процесс-родитель всегда завершается с кодом 0.

Для запуска файла на выполнение используйте execlp.
Не используйте umask для изменения соответствующего параметра процесса.

Например, при запуске вашей программы:

  ./prog wc in.txt out.txt err.txt
В отдельном процессе должна быть запущена программа wc,
ее стандартный ввод должен быть перенаправлен на чтение из файла in.txt,
стандартный вывод - на добавление в файл out.txt, а стандартный поток
ошибок - на перезапись в файл err.txt.
*/
