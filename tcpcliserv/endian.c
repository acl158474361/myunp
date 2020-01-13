#include <stdio.h>
#include <netinet/in.h>

int main(void){
    union uint
    {
        int i;
        char c[sizeof(int)];
    } un;
    
    un.i = 0x0102;
    printf("%d %d %d %d\n", un.c[0], un.c[1], un.c[2], un.c[3]);
    printf("%d\n", un.i);
    un.i = htonl(un.i);
    printf("%d %d %d %d\n", un.c[0], un.c[1], un.c[2], un.c[3]);
    printf("%d\n", un.i);
}