#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char const *argv[]) {
    int status, K;
    struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM
    };
    struct addrinfo *addrs = NULL;

    signal(SIGPIPE, SIG_IGN);

    status = getaddrinfo(argv[1], argv[2], &hints, &addrs);
    if (status) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 0;
    }

    int sockfd = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
    if (sockfd == -1) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        return 0;
    }

    status = connect(sockfd, addrs->ai_addr, addrs->ai_addrlen);
    if (status == -1) {
        fprintf(stderr, "connect error: %s\n", strerror(errno));
        return 0;
    }

    int sockfd2 = dup(sockfd);
    if (sockfd2 == -1) {
        fprintf(stderr, "dup error: %s\n", strerror(errno));
        return 0;
    }

    FILE *fd_host = fdopen(sockfd, "r");
    if (!fd_host) {
        fprintf(stderr, "fdopen error: %s\n", strerror(errno));
        return 0;
    }

    FILE *fd_server = fdopen(sockfd2, "w");
    if (!fd_server) {
        fprintf(stderr, "fdopen error: %s\n", strerror(errno));
        return 0;
    }

    status = fprintf(fd_server, "%s\n", argv[3]);
    fflush(fd_server);
    if (status < 0) {
        fprintf(stderr, "write error: %s\n", strerror(errno));
        return 0;
    }

    status = fscanf(fd_host, "%d", &K);
    if (status < 0) {
        fprintf(stderr, "read error: %s\n", strerror(errno));
        return 0;
    }

    for (int i = 0; i <= K; ++i) {
        status = fprintf(fd_server, "%d\n", i);
        fflush(fd_server);
        if (status < 0) {
            fprintf(stderr, "write error: %s\n", strerror(errno));
            return 0;
        }
    }

    unsigned long long num;
    status = fscanf(fd_host, "%llu", &num);
    if (status < 0) {
        fprintf(stderr, "read error: %s\n", strerror(errno));
        return 0;
    }

    printf("%llu\n", num);
    fflush(stdout);

    fclose(fd_host);
    fclose(fd_server);

    freeaddrinfo(addrs);

    return 0;
}

/*
В аргументах командной строки задаются имя хоста HOST,
имя сервиса (номер порта) SERVICE и некоторый строковый параметр KEY.
Программа должна подключиться к заданному хосту и сервису по протоколу TCP.
Программа отправляет на сервер строку KEY. В ответ сервер посылает клиенту
целое число K > 0. Клиент отправляет серверу числа от 0 до K включительно,
после чего ждет ответа от сервера - целого беззнакового 64-битного числа,
которое выводит на стандартный поток вывода, после чего завершает работу.

Обмен данными клиента и сервера ведется в текстовом виде.
Не забывайте выводить разделитель и сбрасывать буфер.

При разрыве соединения клиент должен завершить работу с кодом завершения 0.
*/
