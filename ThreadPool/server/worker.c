#include "threadPool.h"
int makeWorker(threadPool_t *threadPool){
    for(int i = 0; i < threadPool->workerNum; ++i){
        pthread_create(&threadPool->tidArr[i],NULL,threadFunc,threadPool);
    }
    return 0;
}
//void unlock(void *arg){
//    pthread_mutex_t * pmutex = (pthread_mutex_t *)arg;
//    pthread_mutex_unlock(pmutex);
//}
//void *threadFunc(void *arg){
//    threadPool_t *threadPool = (threadPool_t *)arg;
//    while(1){
//        // 取出任务
//        int netfd;
//        pthread_mutex_lock(&threadPool->taskQueue.mutex);
//        pthread_cleanup_push(unlock,&threadPool->taskQueue.mutex);
//        while(threadPool->taskQueue.queueSize == 0){
//            pthread_cond_wait(&threadPool->taskQueue.cond, &threadPool->taskQueue.mutex);
//        }
//        printf("child get a task!\n");
//        netfd = threadPool->taskQueue.pFront->netfd;
//        deQueue(&threadPool->taskQueue);
//        //pthread_mutex_unlock(&threadPool->taskQueue.mutex);
//        pthread_cleanup_pop(1);
//        // 执行任务
//        transfile(netfd);
//        close(netfd);
//        // 恢复空闲
//        printf("child finish a task!\n");
//    }
//}
void *threadFunc(void *arg){
    threadPool_t *threadPool = (threadPool_t *)arg;
    while(1){
        // 取出任务
        pthread_mutex_lock(&threadPool->taskQueue.mutex);
        while(threadPool->exitflag == 0 && threadPool->taskQueue.queueSize == 0){
            pthread_cond_wait(&threadPool->taskQueue.cond, &threadPool->taskQueue.mutex);
        }
        if(threadPool->exitflag != 0){
            printf("child is going to exit!\n");
            pthread_mutex_unlock(&threadPool->taskQueue.mutex);
            pthread_exit(NULL);
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
