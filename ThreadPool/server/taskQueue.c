#include "taskQueue.h"
int initQueue(taskQueue_t *ptaskQueue){
    bzero(ptaskQueue,sizeof(taskQueue_t));
    pthread_mutex_init(&ptaskQueue->mutex,NULL);
    pthread_cond_init(&ptaskQueue->cond,NULL);
    return 0;
}
int enQueue(taskQueue_t *ptaskQueue, int netfd){
    task_t * pNew = (task_t *)calloc(1,sizeof(task_t));
    pNew->netfd = netfd;
    if(ptaskQueue->queueSize == 0){
        ptaskQueue->pFront = pNew;
        ptaskQueue->pRear = pNew;
    }
    else{
        ptaskQueue->pRear->pNext = pNew;
        ptaskQueue->pRear = pNew;
    }
    ++ptaskQueue->queueSize;
    return 0;
}
int deQueue(taskQueue_t *ptaskQueue){
    task_t * pCur = ptaskQueue->pFront;
    ptaskQueue->pFront = pCur->pNext;
    free(pCur);
    --ptaskQueue->queueSize;
    if(ptaskQueue->queueSize == 0){
        ptaskQueue->pRear = NULL;
    }
    return 0;
}
