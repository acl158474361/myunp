#include <sys/types.h>

struct A{
    u_int64_t a; // 8
    u_int16_t b; // 2
    u_int32_t c; // 4
    u_int64_t d; // 8
};

struct B{
    int a; // 4
    char b; // 1
    short d; // 2
    int c; // 4
    
};
int main(void){
    sizeof(struct B);
}