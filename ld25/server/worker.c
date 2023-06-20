#include "threadPool.h"


int makeWorker(threadPool_t* pthreadPool) {
    for(int i = 0; i < pthreadPool->workerNum; i++) {
        pthread_create(&pthreadPool->tidArr[i], NULL, threadFunc, pthreadPool);
    } 
    return 0;
}

void* threadFunc(void* arg) {
    threadPool_t *pthreadPool = (threadPool_t *)arg;
    while(1) {
        // 取任务
        pthread_mutex_lock(&pthreadPool->taskQueue.mutex);
        while(pthreadPool->taskQueue.queueSize <= 0) {
            pthread_cond_wait(&pthreadPool->taskQueue.cond, &pthreadPool->taskQueue.mutex);
        }
        printf("A child get a task!\n");
        int netfd = pthreadPool->taskQueue.pFront->netfd;
        deQueue(&pthreadPool->taskQueue);
        pthread_mutex_unlock(&pthreadPool->taskQueue.mutex);

        // 做任务
        transfile(netfd);
        close(netfd);

        // 恢复空闲
        printf("child finish a task!\n");
    }
}

