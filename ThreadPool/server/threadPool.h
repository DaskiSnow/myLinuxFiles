#ifndef __THREAD_POOL__
#define __THREAD_POOL__
#include <50func.h>
#include "taskQueue.h"
typedef struct threadPool_s {
    pthread_t *tidArr;
    int workerNum;
    taskQueue_t taskQueue;
} threadPool_t;
typedef struct train_s {
    int length;
    char data[1000];
} train_t;
int initThreadPool(threadPool_t *threadPool, int workerNum);
int makeWorker(threadPool_t *threadPool);
void *threadFunc(void *arg);
int epollAdd(int epfd, int fd);
int epollDel(int epfd, int fd);
int tcpInit(const char *ip, const char *port, int * psockfd);
int transfile(int netfd);
#endif
