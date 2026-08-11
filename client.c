#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    printf("Client Starting...\n");

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("connect");
        return 1;
    }

    printf("Client Connected...\n");

    char *msg = "GET / HTTP/1.1\r\n" "Host: localhost\r\n" "\r\n";

    send(client_socket, msg, strlen(msg), 0);

    char buff[1024];

    int buffer_bytes = recv(client_socket, buff, sizeof(buff), 0);
    buff[buffer_bytes] = '\0';

    printf("recieved: %s\n", buff);

    return 0;
}