#include "threadPool.h"

int exitPipe[2];
void handler(int signum) {
    printf("sig %d is comming!\n", signum);
    write(exitPipe[1],"1", 1);
}
int main(int argc, char* argv[])
{
    // ./server ip port workerNum
    ARGS_CHECK(argc, 4);

    // 总体结构：父进程(单线程), 子进程(主线程+N子线程)
    pipe(exitPipe);
    if(fork()) {
        close(exitPipe[0]);
        signal(SIGUSR1, handler);
        wait(NULL);
        exit(0);
    }
    // 以下都是子进程,即线程池(父进程不能脱离if结构)
    // 初始化核心数据结构threadPool
    close(exitPipe[1]);
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

    // 创建epoll，并将sfd和exitPipe[0]加入监听
    int epfd = epoll_create(1);
    epollAdd(epfd, sfd);
    epollAdd(epfd, exitPipe[0]);

    // 处理来自客户端的请求
    struct epoll_event evs[10];
    while(1) {
        int readyNum = epoll_wait(epfd, evs, SIZE(evs), -1);
        for(int i = 0; i < readyNum; i++) {
            if(evs[i].data.fd == sfd) { // 主线程收到来自客户端的连接
                int netfd = accept(sfd, NULL, NULL);
                pthread_mutex_lock(&threadPool.taskQueue.mutex);
                enQueue(&threadPool.taskQueue, netfd); // 入队
                pthread_cond_broadcast(&threadPool.taskQueue.cond); // 通知子进程
                pthread_mutex_unlock(&threadPool.taskQueue.mutex);
            }
            if(evs[i].data.fd == exitPipe[0]) { // 主线程收到关闭信号
                printf("ThreadPool is going to exit!\n");
                pthread_mutex_lock(&threadPool.taskQueue.mutex);
                threadPool.exitFlag = 1; // 退出标志位置为1
                pthread_cond_broadcast(&threadPool.taskQueue.cond); // 异步唤起同步
                pthread_mutex_unlock(&threadPool.taskQueue.mutex);

                for(int j = 0; j < workerNum; j++) {
                    pthread_join(threadPool.tidArr[j], NULL);
                }
                printf("All exit!\n");
                pthread_exit(NULL);
            }
        }
    }
    return 0;
}

