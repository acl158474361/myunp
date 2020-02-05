#include "unp.h"

int main(void){
    int i, maxi, maxfdp1, listenfd, connfd, sockfd;
    int clients[FD_SETSIZE], nready;
    ssize_t n;
    fd_set rset, allset;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    char buf[MAXLINE], cli_p[INET_ADDRSTRLEN];
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    maxfdp1 = listenfd;
    maxi = -1;
    for(i = 0; i < FD_SETSIZE; ++i){
        clients[i] = -1;
    }
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    for(;;){
        rset = allset;
        nready = Select(maxfdp1+1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(listenfd, &rset)){
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);
            printf("new client: %s, port %d\n", 
                Inet_ntop(AF_INET, &cliaddr.sin_addr, cli_p, sizeof(cli_p)),
                ntohs(cliaddr.sin_port));
            
            for(i = 0; i < FD_SETSIZE; ++i){
                if(clients[i] < 0){
                    clients[i] = connfd;
                    break;
                }
            }
            if(i == FD_SETSIZE){
                err_quit("too many clients");
            }

            FD_SET(connfd, &allset);
            if(connfd > maxfdp1){
                maxfdp1 = connfd;
            }
            if(i > maxi){
                maxi = i;
            }

            if(--nready <= 0){
                continue;
            }
        }

        for(i = 0; i <= maxi; ++i){
            if( (sockfd = clients[i]) < 0){
                continue;
            }
            if(FD_ISSET(sockfd, &rset)){
                if( (n = Read(sockfd, buf, MAXLINE)) == 0){
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    clients[i] = -1;
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