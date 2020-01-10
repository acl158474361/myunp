#include "unp.h"

int main(void){
    int serv_fd, cli_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;
    pid_t pid;

    serv_fd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    Bind(serv_fd, (SA*)&serv_addr, sizeof(serv_addr));
    Listen(serv_fd, LISTENQ);

    for(;;){
        cli_len = sizeof(cli_addr);
        cli_fd = Accept(serv_fd, (SA*)&cli_addr, &cli_len);
        if( (pid = Fork()) == 0){
            Close(serv_fd);
            str_echo(cli_fd);
            exit(0);
        }
        Close(cli_fd);
    }
}