#include "unp.h"
#include "str_echo08.c"

int main(void){
    int serv_fd, cli_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;
    pid_t pid;
    Sigfunc sig_chld;

    serv_fd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    Bind(serv_fd, (SA*)&serv_addr, sizeof(serv_addr));
    Listen(serv_fd, LISTENQ);
    Signal(SIGCHLD, sig_chld); //P110 sig_chld必须调用waitpid 如果调用wait 由于Linux信号不排队 可能只有一部分的子进程被父进程wait 其他子进程变成僵死进程
    for(;;){
        cli_len = sizeof(cli_addr);
        if( (cli_fd = accept(serv_fd, (SA*)&cli_addr, &cli_len)) < 0){
            if(errno == EINTR){
                continue;
            }
            err_sys("accept error");
        }
        if( (pid = Fork()) == 0){
            Close(serv_fd);
            str_echo(cli_fd);
            exit(0);
        }
        Close(cli_fd);
    }
}