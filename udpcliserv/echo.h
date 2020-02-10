#ifndef __ECHO_H__
#define __ECHO_H__

#include <stdio.h>
#include <sys/socket.h>

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr,
    socklen_t servlen);

void dg_echo(int sockfd, struct sockaddr *pcliaddr,
    socklen_t clilen);

#endif