#include "unp.h"
#include <time.h>

int main(int argc, char* argv[]){
    struct sockaddr_in srv_addr, cli_addr;
    int srv_fd, cli_fd;
    socklen_t cli_len;
    char buff[MAXLINE];
    time_t ticks;

    srv_fd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&srv_addr, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(13);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(srv_fd, (SA*)&srv_addr, sizeof(srv_addr));
    Listen(srv_fd, 10);

    for(;;){
        cli_len = sizeof(cli_addr);
        cli_fd = Accept(srv_fd, (SA*)&cli_addr, &cli_len);
        printf("connection from  %s, port %d\n",
            inet_ntop(AF_INET, &cli_addr.sin_addr, buff, sizeof(buff)),
            ntohs(cli_addr.sin_port));
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(cli_fd, buff, strlen(buff));
        Close(cli_fd);

    }
}