#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        return 1;
    }
    int pipes[2];
    pipe(pipes);

    pid_t id, id_2;
    id_2 = fork();
    if (id_2 == -1) {
        fprintf(stderr, "fork\n");
        return 1;
    }
    if (id_2 == 0) {
        dup2(pipes[1], 1);
        close(pipes[1]);
        close(pipes[0]);
        execlp(argv[1], argv[1], NULL);
        perror("exec 0 failed");
        return 1;
    }
    id = fork();
    if (id == -1) {
        fprintf(stderr, "fork error\n");
        return 1;
    }
    if (id == 0) {
        dup2(pipes[0], 0);
        close(pipes[0]);
        close(pipes[1]);
        execvp(argv[2], argv + 2);
        perror("exec 1 failed");
        return 1;
    }
    close(pipes[0]);
    close(pipes[1]);
    int status;
    waitpid(id_2, &status, 0);
    waitpid(id, &status, 0);
    int ok = 0;
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        ok = 1;
    }
    id = fork();
    if (id == -1) {
        fprintf(stderr, "fork\n");
        return 1;
    }
    if (id == 0) {
        execlp("echo","echo", ok ? "ok" : "foo", NULL);
        perror("exec 2 failed");
        return 1;
    }
    wait(NULL);
    return 0;
}
