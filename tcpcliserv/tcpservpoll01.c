#include <limits.h> //C system headers

#include "unp.h" // your project's headers
#define OPEN_MAX 1024

int main(void){
    int i, maxi, listenfd, connfd, sockfd;
    int nready;
    ssize_t n;
    char buf[MAXLINE];
    socklen_t clilen;
    struct pollfd clients[OPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    clients[0].fd = listenfd;
    clients[0].events = POLLIN;
    for(i = 1; i < OPEN_MAX; ++i){
        clients[i].fd = -1;
    }
    maxi = 0;

    for(;;){
        nready = Poll(clients, maxi+1, INFTIM);

        if(clients[0].revents & POLLIN){
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);
            printf("new client: %s\n", Sock_ntop((SA*)&cliaddr, clilen));

            for(i = 1; i < OPEN_MAX; ++i){
                if(clients[i].fd < 0){
                    clients[i].fd = connfd;
                    break;
                }
            }
            if(i == OPEN_MAX){
                err_quit("too many clients");
            }

            clients[i].events = POLLIN;
            if(i > maxi){
                maxi = i;
            }
            if(--nready <= 0){
                continue;
            }
        }

        for(i = 1; i <= maxi; ++i){
            if( (sockfd = clients[i].fd) < 0){
                continue;
            }

            if(clients[i].revents & (POLLIN | POLLERR)){
                if( (n = read(sockfd, buf, MAXLINE)) < 0){
                    if(errno == ECONNRESET){
                        printf("clients[%d] aborted connection\n", i);
                        Close(sockfd);
                        clients[i].fd = -1;
                    }else{
                        err_sys("read error");
                    }
                }else if(n == 0){
                    printf("clients[%d] closed connection\n", i);
                    Close(sockfd);
                    clients[i].fd = -1;
                }else{
                    Writen(sockfd, buf, n);
                }

                if(--nready <= 0){
                    break;
                }
            }
        }
    }

}