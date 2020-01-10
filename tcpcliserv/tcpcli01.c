#include "unp.h"

int main(int argc, char* argv[]){
    int cli_fd;
    struct sockaddr_in serv_addr;
    
    if(argc != 2){
        err_quit("usage: tcpcli <ipaddress>");
    }

    cli_fd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);

    Connect(cli_fd, (SA*)&serv_addr, sizeof(serv_addr));
    str_cli(stdin, cli_fd);
    exit(0);
}