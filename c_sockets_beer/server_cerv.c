#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket_utils.h"

char beer_time[BUFFER_SIZE] = "No hay hora para cerveza propuesta.";

int main() {
    int server_fd, new_socket;
    char buffer[BUFFER_SIZE];

    server_fd = create_server_socket();
    printf("Servidor de cervezas escuchando en el puerto %d...\n", PORT);

    while(1) {
        new_socket = accept_client_connection(server_fd);
        
        receive_data(new_socket, buffer, BUFFER_SIZE);
        printf("Comando recibido: \"%s\"\n", buffer);

        if (strncmp(buffer, "SET ", 4) == 0) {
            char* proposed_time = buffer + 4;
            strncpy(beer_time, proposed_time, BUFFER_SIZE - 1);
            send_data(new_socket, "Hora de cerveza establecida.");
            printf("Hora de cerveza establecida: %s\n", beer_time);
        } else if (strcmp(buffer, "GET") == 0) {
            send_data(new_socket, beer_time);
            printf("Respondiendo con la hora: %s\n", beer_time);
        } else {
            send_data(new_socket, "Comando no reconocido. Use SET <hora> o GET");
        }

        close_connection(new_socket);
    }

    close_connection(server_fd);
    return 0;
}