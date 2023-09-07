#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "8.8.8.8"
#define SERVER_PORT 10080
#define REQUEST_FORMAT "GET / HTTP/1.1\r\nHost: %s\r\n\r\n"

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("inet_pton() failed");
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char request[512];
    snprintf(request, sizeof(request), REQUEST_FORMAT, SERVER_IP);

    if (send(client_socket, request, strlen(request), 0) == -1) {
        perror("Sending request failed");
        exit(EXIT_FAILURE);
    }

    char response[4096];
    int bytes_received = recv(client_socket, response, sizeof(response) - 1, 0);  // -1 to make room for '\0'

    if (bytes_received == -1) {
        perror("Receiving response failed");
        exit(EXIT_FAILURE);
    }

    response[bytes_received] = '\0';
    printf("HTTP Response:\n%s\n", response);
    close(client_socket);  // Close the client socket

    return 0;
}
