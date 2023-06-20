#include "threadPool.h"

int main(int argc, char* argv[])
{
    // ./server ip port workerNum
    ARGS_CHECK(argc, 4);

    // 初始化核心数据结构threadPool
    threadPool_t threadPool;
    int workerNum = atoi(argv[3]);
    int ret = initThreadPool(&threadPool, workerNum);
    ERROR_CHECK(ret, -1, "initTthreadPool");
    
    // 创建子线程
    ret = makeWorker(&threadPool);
    ERROR_CHECK(ret, -1, "makeWorker");

    // 创建listen socket
    int sfd;
    ret = tcpInit(argv[1], argv[2], &sfd);
    ERROR_CHECK(ret, -1, "tcpInit");

    // 创建epoll，并将sfd加入监听
    int epfd = epoll_create(1);
    epollAdd(epfd, sfd);

    // 处理来自客户端的请求
    struct epoll_event evs[10];
    while(1) {
        int readyNum = epoll_wait(epfd, evs, SIZE(evs), -1);
        for(int i = 0; i < readyNum; i++) {
            if(evs[i].data.fd == sfd) {
                int netfd = accept(sfd, NULL, NULL);
                pthread_mutex_lock(&threadPool.taskQueue.mutex);
                enQueue(&threadPool.taskQueue, netfd); // 入队
                pthread_cond_broadcast(&threadPool.taskQueue.cond); // 通知子进程
                pthread_mutex_unlock(&threadPool.taskQueue.mutex);
            }
        }
    }

    return 0;
}

