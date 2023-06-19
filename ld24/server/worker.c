#include <func.h>
#include "head.h"

int makeWorker(int workerNum, workerdata_t* workerdataArr) {
    for(int i = 0; i < workerNum; i++) {
        int spfd[2];
        socketpair(AF_LOCAL, SOCK_STREAM, 0, spfd);

        int pid = fork();
        if(pid == 0) { // 子进程
            close(spfd[0]); // 关闭其中一根管道
            eventLoop(spfd[1]); // 子进程循环处理业务，不许出来
        }
        else { // 父进程记录子进程的pid、pipefd, 并初始化status
            close(spfd[1]); // 关闭对应管道
            workerdataArr[i].pid = pid;
            workerdataArr[i].pipefd = spfd[0];
            workerdataArr[i].status = FREE;
            continue; // 父进程继续创建子进程
        }
    }

    return 0;
}

int eventLoop(int spfd) {
    // 监听epfd, 接收任务, 处理任务, 完成后通知父进程
    while(1) {
        int nfd; // 客户端的连接net socket
        int indexRecv; // 暂存index，方便父进程的完成处理
        recvfd(spfd, &nfd, &indexRecv);
        
        // TODO: 处理客户端的业务请求
        sleep(5);

        // 完成后，通知父进程
        // 初始化msg
        struct msghdr msghdr;
        memset(&msghdr, 0, sizeof(msghdr));
        struct iovec msg_iov[1];
        int indexSend = indexRecv;
        msg_iov[0].iov_base = &indexSend;
        msg_iov[0].iov_len = sizeof(indexSend);
        msghdr.msg_iov = msg_iov;
        msghdr.msg_iovlen = SIZE(msg_iov);

        // 发送完成信息给父进程, 包括index
        sendmsg(spfd, &msghdr, 0);
    }

    return 0;
}
