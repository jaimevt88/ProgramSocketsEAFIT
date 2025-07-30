/*
Cliente TCP Básico

 Este programa implementa un cliente de sockets TCP en C.

 Su propósito es demostrar el flujo fundamental de un cliente de red:

 1.  **Creación del Socket:** Inicializa un punto de comunicación para el cliente.
 2.  **Conexión (Connect):** Intenta establecer una conexión activa con un servidor
 específico, identificado por su dirección IP y número de puerto.
 3.  **Recepción de Datos:** Espera y recibe un mensaje del servidor conectado.
 4.  **Cierre:** Finaliza la conexión con el servidor y cierra el socket del cliente.

 Este código no tiene manejo de errores y asume que un servidor compatible 
 está esperando conexiones en la dirección IP y puerto especificados.

 Para ejecutar:
 1. Compilar: gcc client.c -o client
 2. Ejecutar: ./client

 Las macros PORT y SERVER_IP deben corresponder a las que tiene asignada el servidor

 */

#include <stdio.h>      // printf
#include <string.h>     // strlen
#include <unistd.h>     // close, read
#include <sys/socket.h> // socket, connect
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_pton

#define PORT 8080     
#define SERVER_IP "192.168.56.112" 
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
