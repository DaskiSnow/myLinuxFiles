#include "taskQueue.h"
#include "threadPool.h"
int main(int argc, char *argv[])
{
    // ./server 192.168.118.128 1234 3
    ARGS_CHECK(argc,4);
    int workerNum = atoi(argv[3]);
    threadPool_t threadPool;
    initThreadPool(&threadPool,workerNum);
    makeWorker(&threadPool);
    int sockfd;
    tcpInit(argv[1],argv[2],&sockfd);
    int epfd = epoll_create(1);
    epollAdd(epfd,sockfd);
    struct epoll_event readySet[10];
    while(1){
        int readyNum = epoll_wait(epfd,readySet,10,-1);
        for(int i = 0; i < readyNum; ++i){
            if(readySet[i].data.fd == sockfd){
                int netfd = accept(sockfd,NULL,NULL);
                // 主线通知子线程
                pthread_mutex_lock(&threadPool.taskQueue.mutex);
                enQueue(&threadPool.taskQueue,netfd);
                printf("main send a new task!\n");
                pthread_cond_broadcast(&threadPool.taskQueue.cond);
                pthread_mutex_unlock(&threadPool.taskQueue.mutex);
            }
        }
    }
    return 0;
}

