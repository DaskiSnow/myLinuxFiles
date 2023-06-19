#include "threadPool.h"
int makeWorker(threadPool_t *threadPool){
    for(int i = 0; i < threadPool->workerNum; ++i){
        pthread_create(&threadPool->tidArr[i],NULL,threadFunc,threadPool);
    }
    return 0;
}
void *threadFunc(void *arg){
    threadPool_t *threadPool = (threadPool_t *)arg;
    while(1){
        // 取出任务
        pthread_mutex_lock(&threadPool->taskQueue.mutex);
        while(threadPool->taskQueue.queueSize == 0){
            pthread_cond_wait(&threadPool->taskQueue.cond, &threadPool->taskQueue.mutex);
        }
        printf("child get a task!\n");
        int netfd = threadPool->taskQueue.pFront->netfd;
        deQueue(&threadPool->taskQueue);
        pthread_mutex_unlock(&threadPool->taskQueue.mutex);
        // 执行任务
        transfile(netfd);
        close(netfd);
        // 恢复空闲
        printf("child finish a task!\n");
    }
}
