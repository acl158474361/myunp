#include "unp.h"


int main(int argc, char* argv[]){
    int i, cli_fd[5];
    struct sockaddr_in serv_addr;

    if(argc != 2){
        err_quit("usage: tcpcli <address>");
    }
    for(int i = 0; i < 5; ++i){
        cli_fd[i] = Socket(AF_INET, SOCK_STREAM, 0);
        bzero(&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(SERV_PORT);
        Inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
        Connect(cli_fd[i], (SA*)&serv_addr, sizeof(serv_addr));
    }

    str_cli(stdin, cli_fd[0]);
    exit(0);
}