#ifndef __THREAD_POOL__
#define __THREAD_POOL__
#include <func.h>
#include "taskQueue.h"
typedef struct threadPool_s {
    pthread_t* tidArr;
    int workerNum;
    taskQueue_t taskQueue;
} threadPool_t;
typedef struct train_s {
    int length;
    char data[10000];
} train_t;
int initThreadPool(threadPool_t* pthreadPool, int workerNum);
int makeWorker(threadPool_t* pthreadPool);
void* threadFunc(void* arg);
int epollAdd(int epfd, int fd);
int epollDel(int epfd, int fd);
int tcpInit(const char* ip, const char* port, int* psfd);
int transfile(int netfd);
#endif


