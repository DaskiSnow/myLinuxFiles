#include "head.h"
int main(int argc, char *argv[])
{
    // ./server 192.168.118.128 1234 3
    ARGS_CHECK(argc,4);
    int workerNum = atoi(argv[3]);
    // 为子进程的状态申请内存
    workerdata_t * workerdataArr = (workerdata_t *)calloc(workerNum,sizeof(workerdata_t));
    // 调用函数创建子进程
    makeWorker(workerNum,workerdataArr);
    // 先创建子进程再初始化tcp连接
    // 不让子进程共享sockfd
    int sockfd;
    tcpInit(argv[1],argv[2],&sockfd);
    
    // 创建epoll文件对象
    int epfd = epoll_create(1);
    // 增加监听
    epollAdd(epfd,sockfd);
    // 增加每个子进程管道的监听 
    for(int i = 0; i < workerNum; ++i){
        epollAdd(epfd, workerdataArr[i].pipefd);
    }
    // 等待就绪
    struct epoll_event *readySet = (struct epoll_event *)calloc(workerNum+1,sizeof(struct epoll_event));
    while(1){
        int readyNum = epoll_wait(epfd,readySet,workerNum+1,-1);
        for(int i = 0; i < readyNum; ++i){
            if(readySet[i].data.fd == sockfd){
                printf("1 client connect!\n");
                int netfd = accept(sockfd,NULL,NULL);
                // 父进程将netfd交给子进程
                for(int j = 0; j < workerNum; ++j){
                    if(workerdataArr[j].status == FREE){
                        printf("No %d worker got his job!\n", j);
                        sendfd(workerdataArr[j].pipefd,netfd);
                        workerdataArr[j].status = BUSY;
                        break;
                    }
                }
                close(netfd);//有子进程，则无影响；否则会断开连接
            }
            else{
                // 某个子进程完成了任务
                // 已知文件描述符 找到子进程
                for(int j = 0; j < workerNum; ++j){
                    if(workerdataArr[j].pipefd == readySet[i].data.fd){
                        pid_t pid;
                        read(readySet[i].data.fd,&pid,sizeof(pid));
                        printf("No %d worker finish, pid = %d\n", j, pid);
                        workerdataArr[j].status = FREE;
                        break;
                    }
                }
            }
        }
    }
    return 0;

}

