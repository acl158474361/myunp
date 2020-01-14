#include <stdio.h>
#include <netinet/in.h>

int main(void){
    union uint
    {
        int i;
        char c[sizeof(int)];
    } un;
    
    struct sint{
        int a;
        int b;
    } si;

    si.a = 0x0405;
    si.b = 0x0f0a;

    char* i = (char*)(&si.a);
    printf("%d\n", *(i+4));
    printf("%d\n", *(i+5));
    printf("%d\n", *(i+6));
    printf("%d\n", *(i+7));
    un.i = 0x0102;
    printf("%d %d %d %d\n", un.c[0], un.c[1], un.c[2], un.c[3]);
    printf("%d\n", un.i);
    un.i = htonl(un.i);
    printf("%d %d %d %d\n", un.c[0], un.c[1], un.c[2], un.c[3]);
    printf("%d\n", un.i);
}