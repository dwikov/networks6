#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE 1024

// Driver code
int main() {
    int sockfd;
    char buffer1[MAXLINE], buffer2[MAXLINE];
    struct sockaddr_in servaddr, cliaddr,cliaddr1,cliaddr2;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr1, 0, sizeof(cliaddr1));
    memset(&cliaddr2, 0, sizeof(cliaddr2));
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    cliaddr2.sin_family = AF_INET;
    cliaddr2.sin_addr.s_addr = INADDR_ANY;
    cliaddr2.sin_port = htons(8080);
    cliaddr1.sin_family = AF_INET;
    cliaddr1.sin_addr.s_addr = INADDR_ANY;
    cliaddr1.sin_port = htons(8080);
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len,len1, len2, n1,n2;
    len = sizeof(cliaddr);
    len1 = sizeof(cliaddr1);
    len2 = sizeof(cliaddr2);
    n1 = recvfrom(sockfd, (char *)buffer1, MAXLINE,
                  MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                  &len);
    buffer1[n1] = '\0';
    printf("%s",buffer1);
    sendto(sockfd, (const char *)buffer1, strlen(buffer1),
           MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
           len);
    
    sendto(sockfd, (const char *)buffer1, strlen(buffer1),
           MSG_CONFIRM, (const struct sockaddr *) &cliaddr2, len2);

    printf("msg sent.\n");



    return 0;
}