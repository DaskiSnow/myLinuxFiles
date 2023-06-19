#include "threadPool.h"
int initThreadPool(threadPool_t *threadPool, int workerNum){
    threadPool->tidArr = (pthread_t *)calloc(workerNum,sizeof(pthread_t));
    threadPool->workerNum = workerNum;
    initQueue(&threadPool->taskQueue);
    return 0;
}
