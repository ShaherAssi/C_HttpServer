#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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

    printf("Server Starting...\n");

    if (listen(sock, 5) == -1) {
        perror("listen");
        return 1;
    }

    printf("Server Listening...\n");

    int client_socket = accept(sock, NULL, NULL);
    if (client_socket == -1) {
        perror("accept");
        return 1;
    }
    
    printf("Connected to Client...\n");
    
    char buffer[1024];

    int bytes_buffer = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes_buffer] = '\0';

    printf("recived: %s\n", buffer);

    char *response = "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "Content-Length: 5\r\n"
    "\r\n"
    "Hello";

    send(client_socket, response, strlen(response),0);

    return 0;
}