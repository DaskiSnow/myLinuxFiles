#include "taskQueue.h"
#include "threadPool.h"
int exitPipe[2];
void handler(int signum){
    printf("sig %d is comming!\n", signum);
    write(exitPipe[1],"1",1);
}
int main(int argc, char *argv[])
{
    // ./server 192.168.118.128 1234 3
    ARGS_CHECK(argc,4);
    pipe(exitPipe);
    if(fork() != 0){
        // 父进程
        close(exitPipe[0]);
        signal(SIGUSR1,handler);
        wait(NULL);
        exit(0);
    }// 父进程不能脱离这个if结构
    //子进程 即 线程池
    close(exitPipe[1]);
    int workerNum = atoi(argv[3]);
    threadPool_t threadPool;
    initThreadPool(&threadPool,workerNum);
    makeWorker(&threadPool);
    int sockfd;
    tcpInit(argv[1],argv[2],&sockfd);
    int epfd = epoll_create(1);
    epollAdd(epfd,sockfd);
    epollAdd(epfd,exitPipe[0]);
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
            else if(readySet[i].data.fd == exitPipe[0]){
                printf("threadPool is going to exit!\n");
                //for(int j = 0; j < workerNum; ++j){
                //    pthread_cancel(threadPool.tidArr[j]);
                //}
                pthread_mutex_lock(&threadPool.taskQueue.mutex);
                threadPool.exitflag = 1;//说明退出标志位为1
                pthread_cond_broadcast(&threadPool.taskQueue.cond);
                pthread_mutex_unlock(&threadPool.taskQueue.mutex);

                for(int j = 0; j < workerNum; ++j){
                    pthread_join(threadPool.tidArr[j],NULL);
                }
                printf("done\n");
                pthread_exit(NULL);
            }
        }
    }
    return 0;
}

