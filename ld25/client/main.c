#include "head.h"

int main(int argc, char* argv[])
{
    // ./client serIp serPort
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "socket");

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(sfd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "connect");
    printf("成功连接服务端!\n");

    // 创建epoll文件对象，并增加STDIN和的sfd监听
    int epfd = epoll_create(1);    
    epollAdd(epfd, STDIN_FILENO);
    epollAdd(epfd, sfd);

    // 开启监听
    struct epoll_event evs[2];
    int exitFlag = 0;
    while(1) {
        int readyNum = epoll_wait(epfd, evs, SIZE(evs), -1);
        for(int i = 0; i < readyNum; i++) {
            if(evs[i].data.fd == STDIN_FILENO) { // 来自用户输入
                // 读取命令
                opVar_t opVar;
                initOpvar(&opVar);
                readOp(&opVar);

                // 通过发送命令给服务端(逻辑上的小火车)
                sendcmd(sfd, opVar);

                // 客户端退出
                if(opVar.op == QUIT) {
                    exitFlag = 1;
                    break;
                }
            }
            else if(evs[i].data.fd == sfd) { // 来自服务端的回复或传输内容
                // TODO: 服务端返回操作后的字符串，客户端打印
                // TODO: 服务端传输文件，客户端接收

                // 接收文件
                printf("开始接收文件...\n");
                recvfile(sfd);
                printf("接收完毕！\n");
            }
        }
        if(exitFlag == 1) break;
    }
    close(sfd);
    printf("已断开连接！\n");

    return 0;
}

