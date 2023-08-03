#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#define PORTNO 10200
int main()
{
    int sockfd, newsockfd, portno, clilen, n = 1;
    struct sockaddr_in seraddr, cliaddr;
    char buf[256];
    // Create an unnamed socket for the server
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // Name the socket
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.58.99");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    // Create a connection queue and wait for clients
    listen(sockfd, 5);
    printf("server waiting\n");
    while (1)
    {
        // Accept a connection
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        // Read and write to client on newsockfd
        n = read(newsockfd, buf, sizeof(buf));
        buf[n] = '\0';
        if (strcmp(buf, "Stop") == 0)
        {
            printf("Server terminated by client.\n");
            close(newsockfd);
            break;
        }
        else
        {
            // Logic to find and remove duplicate words
            char result[256] = {0};
            char *word;
            int found = 0;

            word = strtok(buf, " ");
            while (word != NULL)
            {
                // Search for duplicates in the result string
                if (strstr(result, word) == NULL)
                {
                    // Word not found, add to result
                    if (found)
                        strcat(result, " ");
                    strcat(result, word);
                    found = 1;
                }
                word = strtok(NULL, " ");
            }

            // Send the modified sentence to the client
            write(newsockfd, result, strlen(result));
        }

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}

