#include "echo.h"
#include "unp.h"

#define NDG 2000
#define DGLEN 1400
/* void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen){
    int n;
    char sendline[MAXLINE], recvline[MAXLINE+1];
    socklen_t len;
    struct sockaddr reply_addr;
    struct sockaddr *preply_addr = &reply_addr;

    while(Fgets(sendline, MAXLINE, fp) != NULL){
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        len = servlen;
        n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
        if(len != servlen || memcmp(pservaddr, preply_addr, len) != 0){
            printf("reply from %s (ignored)\n",
                    Sock_ntop(preply_addr, len));
            continue;
        }
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }
    
} */

/* void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen){
    int n;
    char sendline[MAXLINE], recvline[MAXLINE+1];

    Connect(sockfd, pservaddr, servlen);
    while(Fgets(sendline, MAXLINE, fp) != NULL){
        Write(sockfd, sendline, strlen(sendline));
        n = Read(sockfd, recvline, MAXLINE);
        recvline[n] = '\0';
        Fputs(recvline, stdout);
    }
} */

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen){
    char sendline[DGLEN];
    for(int i = 0; i < NDG; ++i){
        Sendto(sockfd, sendline, DGLEN, 0, pservaddr, servlen);
    }
}

/* void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen){
    int n;
    socklen_t len;
    char mesg[MAXLINE];

    for(;;){
        len = clilen;
        n = Recvfrom(sockfd, mesg, sizeof(mesg), 0, pcliaddr, &len);

        Sendto(sockfd, mesg, n, 0, pcliaddr, len);
    }
} */

static void recvfrom_int(int);
static int count;

void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen){
    socklen_t len;
    char mesg[MAXLINE];

    Signal(SIGINT, recvfrom_int);
    for(;;){
        len = clilen;
        Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        ++count;
    }
}

static void recvfrom_int(int signo){
    printf("\nreceived %d datagrams\n", count);
    exit(0);
}