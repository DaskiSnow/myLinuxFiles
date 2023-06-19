#include <func.h>
#include "head.h"

int main(int argc, char* argv[])
{
    // ./server ip port workerNum
    ARGS_CHECK(argc, 4);

    // 创建子进程
    int workerNum = atoi(argv[3]);
    workerdata_t *workerdataArr = (workerdata_t *)calloc(workerNum, sizeof(workerdata_t));
    makeWorker(workerNum, workerdataArr);

    // 创建listen socket
    int sfd;
    tcpInit(argv[1], argv[2], &sfd);

    // 创建epoll，并将sfd和子进程pipefd加入监听, 执行监听
    int epfd = epoll_create(1);
    epollAdd(epfd, sfd);
    for(int i = 0; i < workerNum; i++) {
        epollAdd(epfd, workerdataArr[i].pipefd);
    }
    while(1) {
        struct epoll_event evs[10];
        int readyNum = epoll_wait(epfd, evs, SIZE(evs), -1);
        for(int i = 0; i < readyNum; i++) {
            // 来自客户端的连接请求
            if(evs[i].data.fd == sfd) { 
                int nfd = accept(sfd, NULL, NULL); // TODO: 获取客户端信息

                // 查找空闲子进程
                int index = 0;
                for(int j = 0; j < workerNum; j++) {
                    if(workerdataArr[j].status != FREE) continue;
                    index = j;
                }

                // 没有空闲子进程
                if(index == workerNum) { 
                    close(nfd);
                    continue;
                }

                // 有空闲子进程，发送nfd
                sendfd(workerdataArr[index].pipefd, nfd, index);

                // 更新子进程状态
                workerdataArr[index].status = BUSY;
            }
            // 来自子进程的消息 
            else { 
                // 获取对应子进程的pipefd
                int pipefd = 0;
                for(int j = 0; i < workerNum; j++) {
                    if(evs[i].data.fd != workerdataArr[j].pipefd) continue;
                    pipefd = evs[i].data.fd; 
                    break;
                }

                // 初始化msg
                struct msghdr msghdr;
                memset(&msghdr, 0, sizeof(msghdr));  // 必不能少
                struct iovec msg_iov[1];
                int index = -1;
                msg_iov[0].iov_base = &index; 
                msg_iov[0].iov_len = sizeof(index);
                msghdr.msg_iovlen = SIZE(msg_iov);

                // 接收子进程信息，获取子进程index
                recvmsg(pipefd, &msghdr, 0);   

                // 根据子进程index，修改子进程状态
                workerdataArr[index].status = FREE; 
            }
        }
    } 
    return 0;
}

