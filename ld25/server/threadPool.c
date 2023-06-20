#include "threadPool.h"

int initThreadPool(threadPool_t* pthreadPool, int workerNum) {
    pthreadPool->tidArr = (pthread_t *)calloc(workerNum, sizeof(pthread_t));
    pthreadPool->workerNum = workerNum;
    initQueue(&pthreadPool->taskQueue);
    return 0;
}


