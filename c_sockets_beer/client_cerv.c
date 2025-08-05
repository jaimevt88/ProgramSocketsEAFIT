#include <stdio.h>
#include <string.h>
#include "socket_utils.h"

#define SERVER_IP "127.0.0.1"

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <comando> [hora]\n", argv[0]);
        printf("Ejemplos:\n");
        printf("  %s GET\n", argv[0]);
        printf("  %s SET 18:00\n", argv[0]);
        return 1;
    }

    int sock = create_client_socket_and_connect(SERVER_IP);
    printf("Conectado al servidor de cervezas.\n");
    
    char command[BUFFER_SIZE];
    if (strcmp(argv[1], "GET") == 0) {
        strcpy(command, "GET");
    } else if (strcmp(argv[1], "SET") == 0 && argc >= 3) {
        snprintf(command, BUFFER_SIZE, "SET %s", argv[2]);
    } else {
        printf("Comando inválido.\n");
        close_connection(sock);
        return 1;
    }

    send_data(sock, command);
    printf("Comando enviado: \"%s\"\n", command);

    char buffer[BUFFER_SIZE];
    receive_data(sock, buffer, BUFFER_SIZE);
    printf("Respuesta del servidor: \"%s\"\n", buffer);

    close_connection(sock);
    printf("Cliente cerrado.\n");

    return 0;
}