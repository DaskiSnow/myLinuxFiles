#include "head.h"
int main(int argc, char *argv[])
{
    // ./server 192.168.118.128 1234 3
    ARGS_CHECK(argc,4);
    int workerNum = atoi(argv[3]);
    // 为子进程的状态申请内存
    workerdata_t * workerdataArr = (workerdata_t *)calloc(workerNum,sizeof(workerdata_t));
    // 调用函数创建子进程
    makeWorker(workerNum,workerdataArr);
    // 先创建子进程再初始化tcp连接
    // 不让子进程共享sockfd
    int sockfd;
    tcpInit(argv[1],argv[2],&sockfd);
    pause();
    return 0;
}

