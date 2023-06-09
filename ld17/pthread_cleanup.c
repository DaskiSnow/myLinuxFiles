#include <func.h>

void free1(void* arg){
    free(arg);
}

int main(int argc, char* argv[])
{
    int* pnum = (int*)malloc(sizeof(int));
    pthread_cleanup_push(free1, pnum);
    pthread_cleanup_pop(1);
    return 0;
}

