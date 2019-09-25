#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char const *argv[]) {
    struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM
    };
    struct addrinfo *addrs = NULL;

    char host[INET_ADDRSTRLEN];
    char service[INET_ADDRSTRLEN];

    while (scanf("%s %s", host, service) == 2) {
        int status = getaddrinfo(host, service, &hints, &addrs);
        if (status) {
            printf("%s\n", gai_strerror(status));
            continue;
        }
        struct sockaddr_in *psin_min = NULL;
        unsigned long int addr_min = ULONG_MAX;

        for (struct addrinfo *pa = addrs; pa; pa = pa->ai_next) {
            struct sockaddr_in *psin = (struct sockaddr_in *) pa->ai_addr;
            unsigned long int addr_tmp = ntohl(psin->sin_addr.s_addr);
            if (addr_min > addr_tmp) {
                addr_min = addr_tmp;
                psin_min = psin;
            }
        }
        printf("%s:%d\n", inet_ntoa(psin_min->sin_addr),
            ntohs(psin_min->sin_port));

        freeaddrinfo(addrs);

    }

    return 0;
}

/*
На стандартный поток ввода подаются текстовые строки, не превышающие в длину
1000 символов. Каждая текстовая строка содержит имя хоста и имя сервиса,
каждое из которых является символьными строками.

Для каждой пары HOST SERVICE на стандартный поток вывода напечатайте адрес
IPv4 и номер порта.

Если имя HOST отображается в несколько IP-адресов, выводите IP-адрес,
представление которого в локальном порядке байт (32 бита) минимально.

Если при отображении возникла ошибка, на стандартный поток вывода напечатайте
текстовое сообщение об ошибке.

Используйте функции getaddrinfo, gai_strerror, freeaddrinfo, inet_ntoa,
ntohs, ntohl.

Примечание. Текущий IP-адрес хоста google.com может отличаться от
приведенного в примере.

Примеры:
Входные данные:

google.com https
go.go 25

Результат работы:

173.194.32.128:443
No address associated with hostname
*/
