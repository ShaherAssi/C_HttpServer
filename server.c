#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    if (bind(sock, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind"); //tells you why the bind function failed.
        return 1;
    }

    if (listen(sock, 5) == -1) {
        perror("listen");
        return 1;
    }

    return 0;
}