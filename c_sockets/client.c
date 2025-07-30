#include <stdio.h>      // printf
#include <string.h>     // strlen
#include <unistd.h>     // close, read
#include <sys/socket.h> // socket, connect
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_pton

#define PORT 8080     
#define SERVER_IP "127.0.0.1" 
#define BUFFER_SIZE 1024      

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Conectado al servidor simple en %s:%d\n", SERVER_IP, PORT);

    read(sock, buffer, BUFFER_SIZE - 1);
    buffer[BUFFER_SIZE - 1] = '\0';

    printf("Mensaje recibido: \"%s\"\n", buffer);

    close(sock);
    printf("Cliente cerrado.\n");

    return 0;
}
