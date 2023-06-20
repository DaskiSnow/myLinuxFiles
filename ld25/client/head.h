#include <func.h>
typedef struct train_s {
    int length;
    char data[10000];
} train_t;

int recvn(int netfd, void* buf, int length);
int recvfile(int netfd); 
