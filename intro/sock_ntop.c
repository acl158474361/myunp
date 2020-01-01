#include "unp.h"

char* sock_ntop(const struct sockaddr* sa, socklen_t len){
    static char str[128];
    char str_port[8];
    switch (sa->sa_family)
    {
    case AF_INET:
        const struct sockaddr_in *sin = (const struct sockaddr_in*)sa;
        if(inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL){
            return NULL;
        }
        if(ntohs(sin->sin_port) != 0){
            snprintf(str_port, sizeof(str_port), ":%d", ntohs(sin->sin_port));
            strcat(str, str_port);
        }
        break;
    
    default:
        return NULL;
    }
    return str;
}