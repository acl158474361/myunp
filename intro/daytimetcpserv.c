#include "unp.h"
#include <time.h>

int main(int argc, char* argv[]){
    int serv_sockfd, cli_sockfd;
    struct sockaddr_in serv_addr;
    char buf[MAXLINE];
    time_t ticks;

    if( (serv_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        err_sys("socket error");
    }
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(13);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(serv_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){ //因为Linux的套接字地址结构没有长度字段，所以要提供第三个参数 
        err_sys("bind error");
    }
    if(listen(serv_sockfd, 10) < 0){
        err_sys("listen error");
    }
    for(;;){
        cli_sockfd = Accept(serv_sockfd, NULL, NULL);
        ticks = time(NULL);
        snprintf(buf, MAXLINE-1, "%.24s\r\n", ctime(&ticks));
        write(cli_sockfd, buf, strlen(buf));
        close(cli_sockfd);
    }
}