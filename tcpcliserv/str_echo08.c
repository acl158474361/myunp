#include "unp.h"

void str_echo(int sockfd){
    long rand1, rand2;
    char line[MAXLINE];

    for(;;){
        if(Readline(sockfd, line, MAXLINE) == 0){
            return;
        }
        printf("%s", line);
        if(sscanf(line, "%ld%ld", &rand1, &rand2) == 2){
            snprintf(line, sizeof(line), "%ld\n", rand1+rand2);
        }else{
            snprintf(line, sizeof(line), "input error\n");
        }
        Writen(sockfd, line, strlen(line));
    }
}