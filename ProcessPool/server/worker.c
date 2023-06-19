#include "head.h"
int makeWorker(int workerNum,workerdata_t * workerdataArr){
    pid_t pid;
    for(int i = 0; i < workerNum; ++i){
        int sv[2];
        socketpair(AF_UNIX,SOCK_STREAM,0,sv);
        pid = fork();
        if(pid == 0){
            // 只有子进程能进入
            close(sv[0]);
            eventLoop(sv[1]);
            // 让这个if语句块永远无法离开
        }
        // 只有父进程会调用
        close(sv[1]);
        workerdataArr[i].pid = pid;
        workerdataArr[i].status = FREE;
        workerdataArr[i].pipefd = sv[0];
        printf("worker %d, pid = %d, pipefd = %d\n", i, pid, sv[0]);
    }
    return 0;
}
int eventLoop(int sockfd){
    while(1){
        int netfd;
        recvfd(sockfd,&netfd);//接收任务
        // 任务已经收到
        printf("child got job!, netfd = %d\n", netfd);
        sleep(10);
        printf("sleep over!\n");
        
        // 任务已经完成
        close(netfd);
        // 通知父进程
        pid_t pid = getpid();
        write(sockfd,&pid,sizeof(pid));
    }

}
