#include "unp.h"

ssize_t readn(int fd, void *vptr, size_t n){
    ssize_t nread;
    size_t nleft = n;

    while(nleft > 0){
        if( (nread = read(fd, vptr, nleft)) < 0){
            if(errno == EINTR){
                nread = 0;
            }else{
                return -1;
            }
        }else if(nread == 0){
            break;
        }
        nleft -= nread;
        vptr += nread;
    }

    return n-nleft;
}

ssize_t writen(int fd, const void *vptr, size_t n){
    size_t nleft = n;
    ssize_t nwritten;

    while(nleft > 0){
        if( (nwritten = write(fd, vptr, nleft)) <= 0){
            if(nwritten < 0 && errno == EINTR){
                nwritten = 0;
            }else{
                return -1;
            }
        }
        nleft -= nwritten;
        vptr += nwritten;
    }
    return n;
}