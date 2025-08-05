/*

 Servidor TCP Básico

 Este programa implementa un servidor de sockets TCP minimalista en lenguaje C.
 Su propósito es demostrar el flujo fundamental de un servidor de red:

 1.  **Creación del Socket:** Inicializa un punto de comunicación en la red.
 2.  **Enlace (Bind):** Asigna una dirección IP y un número de puerto específicos al socket
 para que el servidor sea accesible.
 3.  **Escucha (Listen):** Pone el socket en modo pasivo para que esté listo para aceptar
 conexiones entrantes de clientes.
 4.  **Aceptación (Accept):** Espera y acepta una única conexión de un cliente. Una vez
 aceptada, se crea un nuevo socket dedicado para esa comunicación.
 5.  **Envío de Datos:** Envía un mensaje predefinido al cliente conectado.
 6.  **Cierre:** Finaliza la conexión con el cliente y luego cierra el socket principal
 del servidor.

 Importante, las macros (constantes) PORT y BUFFER_SIZE deben seleccionarse según su interés
 La constante predefinida INADDR_ANY le dice al SO que acepta conexiones a cualquier IP del host

 Este código no incluye manejo de excepciones
 Solo puede manejar una conexión de cliente a la vez antes de cerrarse.

 Para ejecutar:
 1. Compilar: gcc server.c -o server
 2. Ejecutar: ./server
 3. Luego, ejecutar un cliente compatible para que se conecte a este servidor.
 */



#include <stdio.h>      // printf
#include <string.h>     // strlen
#include <unistd.h>     // close
#include <sys/socket.h> // socket, bind, listen, accept, send
#include <netinet/in.h> // sockaddr_in

#define PORT 8080       
#define BUFFER_SIZE 1024 

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *message = "¡Hola desde el servidor simple en c!";


    server_fd = socket(AF_INET, SOCK_STREAM, 0); // El SO identifica un socket con un descriptor de archivo (entero)

    // Configurar la dirección del servidor
    address.sin_family = AF_INET; //IPv4
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    bind(server_fd, (struct sockaddr *)&address, sizeof(address));


    listen(server_fd, 3);

    printf("Servidor simple escuchando en el puerto %d...\n", PORT);

    // Para la conexión entrante se instancia 
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
