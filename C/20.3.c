#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM
    };
    struct addrinfo *addrs = NULL;

    int status = getaddrinfo(argv[1], argv[2], &hints, &addrs);
    if (status) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 0;
    }

    int sockfd = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
    if (sockfd == -1) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        return 0;
    }

    int val = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(strtol(argv[1], NULL, 10));
    addr.sin_addr.s_addr = INADDR_ANY;

    status = bind(sockfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_in));
    if (status == -1) {
        fprintf(stderr, "bind error: %s\n", strerror(errno));
        return 1;
    }

    status = listen(sockfd, 5);
    if (status == -1) {
        fprintf(stderr, "listen error: %s\n", strerror(errno));
        return 1;
    }

    while (1) {
        int size = sizeof(addr);
        int new_fd = accept(sockfd, (struct sockaddr*) &addr, (socklen_t*) &size);
        if (new_fd == -1) {
            fprintf(stderr, "accept error: %s\n", strerror(errno));
            return 0;
        }

        if (!fork()) {
            close(sockfd);
            char c;
            while (read(new_fd, &c, 1) == 1) {
                write(1, &c, 1);
            }

            write(new_fd, "Hello\n", 6);
            _exit(0);
        } else {
            wait(NULL);
        }
        close(new_fd);
    }

    freeaddrinfo(addrs);

    return 0;
}
