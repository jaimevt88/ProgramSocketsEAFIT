#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

char beer_time[BUFFER_SIZE] = "No hay hora para cerveza propuesta.";

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    printf("Servidor de cervezas escuchando en el puerto %d...\n", PORT);

    while(1) { // Loop infinito para aceptar múltiples conexiones
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        memset(buffer, 0, BUFFER_SIZE); // Limpiar buffer

        read(new_socket, buffer, BUFFER_SIZE - 1);
        printf("Comando recibido: \"%s\"\n", buffer);

        // Lógica para procesar los comandos
        if (strncmp(buffer, "SET ", 4) == 0) {
            // El comando SET viene con el formato "SET <hora>"
            char* proposed_time = buffer + 4;
            strncpy(beer_time, proposed_time, BUFFER_SIZE - 1);
            send(new_socket, "Hora de cerveza establecida.", strlen("Hora de cerveza establecida."), 0);
            printf("Hora de cerveza establecida: %s\n", beer_time);
        } else if (strcmp(buffer, "GET") == 0) {
            // El comando GET
            send(new_socket, beer_time, strlen(beer_time), 0);
            printf("Respondiendo con la hora: %s\n", beer_time);
        } else {
            // Comando no reconocido
            send(new_socket, "Comando no reconocido. Use SET <hora> o GET", strlen("Comando no reconocido. Use SET <hora> o GET"), 0);
        }

        close(new_socket); // Cierra la conexión con el cliente actual
    }

    close(server_fd);
    return 0;
}
