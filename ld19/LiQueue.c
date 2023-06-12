#include <func.h>
#include "LiQueue.h"

void queue_create(LiQueue** ppqueue) {
     *ppqueue = (LiQueue*)calloc(1, sizeof(LiQueue));
    if(!(*ppqueue)) {
        printf("calloc failed in queue_create.\n");
        exit(1);
    }
    return;
}

void queue_destroy(LiQueue* pqueue) {
    while(pqueue->front){
        Node* next = pqueue->front->next;
        free(pqueue->front);
        pqueue->front = next;
    }
    // 释放结构体
    free(pqueue);
}

void queue_push(LiQueue* pqueue, int no) {
    // 创建新结点
    Node* new_node = (Node*)calloc(1, sizeof(Node));
    if(!new_node) {
        printf("calloc failed in queue_push.\n");
        exit(1);
    }
    
    // 初始化结点
    new_node->no = no;
    new_node->next = NULL;

    // 入队
    if(queue_empty(pqueue)) {
        pqueue->front = new_node;
        pqueue->rear = new_node;
    }
    else {
        pqueue->rear->next = new_node;
        pqueue->rear = new_node;
    }
}

void queue_pop(LiQueue* pqueue, int *pno) {
    // 判空
    if(queue_empty(pqueue)) {
        printf("queue_pop failed due to queue empty.\n");
        exit(1);
    }

    *pno = pqueue->front->no;
    Node* next = pqueue->front->next;
    free(pqueue->front);
    pqueue->front = next;
}

void queue_peek(LiQueue* pqueue, int *pno) {
    // 判空 
    if(queue_empty(pqueue)) {
        printf("queue_pop failed due to queue empty.\n");
        exit(1);
    }

    *pno = pqueue->front->no;
}

bool queue_empty(LiQueue* pqueue) {
    return pqueue->front == NULL;
}

