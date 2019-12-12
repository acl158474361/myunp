#include <netdb.h>

#include "unp.h"

int main(int argc, char* argv[]){
    struct addrinfo *aip, *ailist;
    char addrbuf[INET_ADDRSTRLEN];
    int err;
    const char *addr;
    if(argc != 2){
        err_quit("usage: a.out <hostname>");
    }
    if( (err = getaddrinfo(argv[1], NULL, NULL, &ailist)) < 0){
        err_quit("getaddrinfo error: %s", gai_strerror(err));
    }
    for(aip = ailist; aip != NULL; aip = aip->ai_next){
        if(aip->ai_family == AF_INET){
            addr = inet_ntop(AF_INET, &((struct sockaddr_in *)aip->ai_addr)->sin_addr, addrbuf, INET_ADDRSTRLEN);
            printf("%s\n", addr);
        }
    }
}