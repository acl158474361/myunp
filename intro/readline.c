#include "unp.h"

static char read_buf[MAXLINE];
static ssize_t read_cnt;
static char *buf_ptr;

static ssize_t my_read(int fd, char *c){
    if(read_cnt <= 0){
    again:
        if( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0){
            if(errno == EINTR){
                goto again;
            }
            return -1;
        }else if(read_cnt == 0){
            return 0;
        }
        buf_ptr = read_buf;
    }
    --read_cnt;
    *c = *buf_ptr++;
    return 1;
}


ssize_t readline_1(int fd, void *vptr, ssize_t maxlen){
    ssize_t n, nr;
    char *cp = vptr;
    for(n = 1; n < maxlen; ++n){
        if( (nr = my_read(fd, cp)) < 0){
            return -1;
        }
        if(nr == 0){
            *cp = '\0';
            return n-1;
        }
        if(*cp++ == '\n'){
            *cp = '\0';
            return n;
        }
    }
    *cp = '\0';
    return n-1;
}

int main(void){
    char buf[10];
    int count = readline_1(STDIN_FILENO, buf, sizeof(buf));
    
}