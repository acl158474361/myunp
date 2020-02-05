#include "strcli.h"

#include "unp.h" // your project's .h files


/* void str_cli(FILE *fp, int sockfd){
    int maxfdp1;
    fd_set rset;
    char sendline[MAXLINE], recvline[MAXLINE];

    FD_ZERO(&rset);
    for(;;){
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(sockfd, &rset)){
            if(Readline(sockfd, recvline, MAXLINE) == 0){
                err_quit("str_cli: server terminated prematurely");
            }
            Fputs(recvline, stdout);
        }

        if(FD_ISSET(fileno(fp), &rset)){
            if(Fgets(sendline, MAXLINE, fp) == NULL){
                return;
            }
            Writen(sockfd, sendline, strlen(sendline));
        }
        
    }
} */

void str_cli(FILE *fp, int sockfd){
    int maxfdp1;
    int endin = 0;
    char buf[MAXLINE];
    fd_set rset;
    int n;
    FD_ZERO(&rset);
    for(;;){
        if(endin == 0){
            FD_SET(fileno(fp), &rset);
        }
        FD_SET(sockfd, &rset);
        maxfdp1 = max(sockfd, fileno(fp)) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(sockfd, &rset)){
            if( (n = Read(sockfd, buf, MAXLINE)) == 0){
                if(endin == 1){
                    return;
                }
                err_quit("str_cli: server terminated prematurely");
            }
            Writen(STDOUT_FILENO, buf, n);
        }

        if(FD_ISSET(fileno(fp), &rset)){
            if( (n = Read(fileno(fp), buf, MAXLINE)) == 0){
                endin = 1;
                Shutdown(sockfd, SHUT_WR);
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            Writen(sockfd, buf, n);
        }
    }

    
}