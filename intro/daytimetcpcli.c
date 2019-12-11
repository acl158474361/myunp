#include "unp.h"

int main(int argc, char* argv[]){
    int cli_sockfd;
    struct sockaddr_in serv_addr;
    int nr;
    char line[MAXLINE];
    if(argc != 2){
        err_quit("usage: a.out <ipaddress>");
    }
    if( (cli_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        err_sys("socket error");
    }
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(13);
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr.s_addr) <=0){
        err_quit("inet_pton error for %s", argv[1]);
    }

    if(connect(cli_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        err_sys("connect error");
    }
    while( (nr = read(cli_sockfd, line, MAXLINE-1)) > 0){
        line[nr] = '\0';
        if(fputs(line,stdout) == EOF){
            err_sys("fputs error");
        }
    }
    if(nr < 0){
        err_sys("read error");
    }
    exit(0);
}