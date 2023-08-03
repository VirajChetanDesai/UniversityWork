#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int len, result, sockfd, n = 1;
    struct sockaddr_in address;
    char ch[256], buf[256];

    // Create a socket for the client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Name the socket as agreed with the server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.58.99");
    address.sin_port = htons(10200);
    len = sizeof(address);

    // Connect your socket to the server’s socket
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }

    while (1)
    {
        // You can now read and write via sockfd
        printf("\nENTER STRING (type 'Stop' to terminate):\n");
        gets(ch);
        ch[strlen(ch)] = '\0';

        // Send the input sentence to the server
        write(sockfd, ch, strlen(ch));

        if (strcmp(ch, "Stop") == 0)
        {
            printf("Client terminated.\n");
            break;
        }
        else
        {
            // Receive and display the modified sentence from the server
            n = read(sockfd, buf, sizeof(buf));
            buf[n] = '\0';
            printf("\nReceived from Server: %s\n", buf);
        }
    }

    close(sockfd);
    return 0;
}

