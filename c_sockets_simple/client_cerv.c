#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "192.168.56.112" 
#define BUFFER_SIZE 1024

int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if (argc < 2) {
        printf("Uso: %s <comando> [hora]\n", argv[0]);
        printf("Ejemplos:\n");
        printf("  %s GET\n", argv[0]);
        printf("  %s SET 18:00\n", argv[0]);
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Conectado al servidor de cervezas.\n");

    char command[BUFFER_SIZE];
    if (strcmp(argv[1], "GET") == 0) {
        strcpy(command, "GET");
    } else if (strcmp(argv[1], "SET") == 0 && argc >= 3) {
        snprintf(command, BUFFER_SIZE, "SET %s", argv[2]);
    } else {
        printf("Comando inválido.\n");
        close(sock);
        return 1;
    }

    send(sock, command, strlen(command), 0);
    printf("Comando enviado: \"%s\"\n", command);

    read(sock, buffer, BUFFER_SIZE - 1);
    printf("Respuesta del servidor: \"%s\"\n", buffer);

    close(sock);
    return 0;
}
