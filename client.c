#include <sys/socket.h>

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    return 0;
}