#include <func.h>

int main(){
    unsigned short us = 0x1234;
    printf("%x\n",us);
    unsigned short us1 = htons(us);//将端口号从小端转换成大端
    printf("%x\n",us1);
    printf("%x\n",ntohs(us1));
    return 0;
}
