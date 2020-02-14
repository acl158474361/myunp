#include "unp.h"

int main(int argc, char** argv){
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;
    int sockfd;

    if(argc != 2){
        err_quit("usage: udpcli <IPaddress>");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

    len = sizeof(cliaddr);
    Getsockname(sockfd, (SA*)&cliaddr, &len);
    printf("local address %s\n", Sock_ntop((SA*)&cliaddr, len));

    exit(0);


}