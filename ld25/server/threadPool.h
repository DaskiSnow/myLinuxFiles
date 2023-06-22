#ifndef __THREAD_POOL__
#define __THREAD_POOL__
#include <func.h>
#include "taskQueue.h"
#define NETDISK_LOG_DEBUG(retval, val, msg){   \
    if(retval == val){                         \
    printf("%s:%s\n",msg,strerror(errno));     \
    printf("file = %s\n", __FILE__);           \
    printf("func = %s\n", __FUNCTION__);       \
    printf("line = %d\n", __LINE__);           \
    }                                          \
}

// 存储子线程信息(主线程除外)
typedef struct threadPool_s { 
    pthread_t* tidArr;      // 子线程tid
    int workerNum;          // 子线程数目
    taskQueue_t taskQueue;  // 任务队列
    int exitFlag;           // 退出标志位
} threadPool_t;

// 小火车
typedef struct train_s { 
    int length;
    char data[10000];
} train_t;

// 操作枚举 
enum {
    CD,
    LS,
    PUTS,
    GETS,
    REMOVE,
    PWD,
    QUIT
};

// 操作变量
typedef struct opVar_s {
    int op;         // 操作
    int argc;       // 参数个数
    char* argv[10]; // 参数token集合, 需要预先分配空间
} opVar_t;

int initThreadPool(threadPool_t* pthreadPool, int workerNum);
int makeWorker(threadPool_t* pthreadPool);
void* threadFunc(void* arg);
int epollAdd(int epfd, int fd);
int epollDel(int epfd, int fd);
int tcpInit(const char* ip, const char* port, int* psfd);
int transfile(int netfd);
int recvn(int netfd, void* buf, int length);
void initOpVar(opVar_t *pOpvar);
void destroyOpVar(opVar_t *pOpvar);
int recvcmd(int netfd, opVar_t* opVar);

#endif


