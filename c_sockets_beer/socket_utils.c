/*
 socket_utils.c
 Este archivo implementa una librería de funciones genéricas de sockets en C,
 diseñadas para ser reutilizadas en aplicaciones cliente y servidor. 

 El propósito de esta librería es encapsular las llamadas de bajo nivel del sistema
 operativo para la creación, conexión, y comunicación a través de sockets TCP.
 Esto permite que el código de las aplicaciones principales
 sea más limpio, legible y se enfoque en la lógica de negocio, en lugar de 
 los detalles de la programación de red.

1. Funciones del Servidor
create_server_socket(): Inicializa un socket, lo enlaza a una dirección IP y un puerto predefinidos (PORT), 
y lo pone en modo de escucha (listen) para aceptar conexiones entrantes. Retorna un descriptor de archivo para el socket del servidor.

accept_client_connection(): Es una función bloqueante que espera por una conexión de cliente.
 Cuando un cliente se conecta, crea un nuevo socket para la comunicación dedicada con ese cliente y retorna su descriptor de archivo.

2. Funciones del Cliente
create_client_socket_and_connect(): Crea un socket, y luego intenta conectarse a una dirección IP y puerto de servidor específicos. 
Retorna el descriptor de archivo del socket una vez que la conexión se ha establecido.

3. Funciones Comunes
Estas funciones se usan tanto en el servidor (para comunicarse con un cliente) como en el cliente (para comunicarse con el servidor):

send_data(): Envía una cadena de caracteres (data) a través del socket especificado.

receive_data(): Lee datos del socket en un búfer (buffer) y retorna la cantidad de bytes recibidos.

close_connection(): Cierra un socket, liberando los recursos de red asociados.


 */

#include "socket_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int create_server_socket() {
    int server_fd;
    struct sockaddr_in address;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    
    return server_fd;
}


int accept_client_connection(int server_fd) {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int new_socket;

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    return new_socket;
}


int create_client_socket_and_connect(const char *server_ip) {
    int sock = 0;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, server_ip, &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    return sock;
}


int send_data(int sockfd, const char *data) {
    return send(sockfd, data, strlen(data), 0);
}


int receive_data(int sockfd, char *buffer, int buffer_size) {
    memset(buffer, 0, buffer_size);
    return read(sockfd, buffer, buffer_size - 1);
}


void close_connection(int sockfd) {
    close(sockfd);
}