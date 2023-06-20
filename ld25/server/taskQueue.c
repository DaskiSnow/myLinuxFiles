#include "taskQueue.h"

int initQueue(taskQueue_t *ptaskQueue){
    memset(ptaskQueue, 0, sizeof(taskQueue_t));
    pthread_mutex_init(&ptaskQueue->mutex, NULL);
    pthread_cond_init(&ptaskQueue->cond, NULL);
}

int enQueue(taskQueue_t *ptaskQueue, int netfd){
    task_t *newTask = (task_t *)calloc(1, sizeof(task_t));
    newTask->netfd = netfd;

    if(ptaskQueue->queueSize == 0) {
        ptaskQueue->pFront = newTask;
        ptaskQueue->pRear = newTask;
    }
    else {
        ptaskQueue->pRear->pNext = newTask;
        ptaskQueue->pRear = newTask;
    }
    ptaskQueue->queueSize++;

    return 0;
}

int deQueue(taskQueue_t *ptaskQueue){
    if(ptaskQueue->queueSize == 0) return -1;
    task_t *ptask = ptaskQueue->pFront;
    ptaskQueue->pFront = ptask->pNext;
    free(ptask);
    ptaskQueue->queueSize--;
    if(ptaskQueue->queueSize == 0) {
        ptaskQueue->pRear = NULL;
    }
    return 0;
}



