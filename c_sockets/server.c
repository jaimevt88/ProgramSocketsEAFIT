#include <stdio.h>      // printf
#include <string.h>     // strlen
#include <unistd.h>     // close
#include <sys/socket.h> // socket, bind, listen, accept, send
#include <netinet/in.h> // sockaddr_in

#define PORT 8080       // Puerto
#define BUFFER_SIZE 1024 // Tamaño del buffer

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *message = "Hola desde el servidor simple!";

    // 1. Crear el socket del servidor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Configurar la dirección del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 2. Enlazar el socket a una dirección y puerto
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // 3. Poner el socket en modo de escucha
    listen(server_fd, 3);

    printf("Servidor simple escuchando en el puerto %d...\n", PORT);

    // 4. Aceptar una conexión entrante
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // 5. Enviar el mensaje al cliente
    send(new_socket, message, strlen(message), 0);
    printf("Mensaje enviado: \"%s\"\n", message);

    // 6. Cerrar sockets
    close(new_socket);
    close(server_fd);

    printf("Servidor simple cerrado.\n");

    return 0;
}
