#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include <sys/socket.h>

#define BUFFER_SIZE 1024
#define PORT 8080


int create_server_socket();
int accept_client_connection(int server_fd);


int create_client_socket_and_connect(const char *server_ip);


int send_data(int sockfd, const char *data);
int receive_data(int sockfd, char *buffer, int buffer_size);
void close_connection(int sockfd);

#endif 