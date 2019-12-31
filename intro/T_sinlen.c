#include <stdio.h>

#include "unp.h"


int main(void){
    // Linux 上 的所有地址结构都没有长度字段
    struct sockaddr_in sin;
    struct sockaddr sa;
    struct sockaddr_in6 sin6;
    struct sockaddr_un su;
    sizeof(sin);
    sizeof(sin6);
}