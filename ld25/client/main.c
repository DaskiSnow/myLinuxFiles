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

    int is_authenticated = 0;
    while(is_authenticated == 0) { // TODO: 封装成函数，并解决退出问题
        // 用户登录
        int wrongCount = 0; // 登录出错次数
        char username[1024] = {0};
        char passwd[1024] = {0};
        printf("输入用户名:");
        fflush(stdout);
        read(STDIN_FILENO, username, sizeof(username));
        username[strlen(username)-1] = '\0';
        printf("输入密码:");
        fflush(stdout);
        read(STDIN_FILENO, passwd, sizeof(passwd));
        passwd[strlen(passwd)-1] = '\0';
        // 发送登录信息(逻辑上小火车发送)
        int length = strlen(username);
        send(sfd, &length, sizeof(int), MSG_NOSIGNAL);
        send(sfd, username, strlen(username), MSG_NOSIGNAL);
        length = strlen(passwd);
        send(sfd, &length, sizeof(int), MSG_NOSIGNAL);
        send(sfd, passwd, strlen(passwd), MSG_NOSIGNAL); // TODO: 目前明文传输，后续密文传输
        // 等待接收鉴权结果
        printf("正在登录...\n");
        recvn(sfd, &is_authenticated, sizeof(int));
        if(is_authenticated != 0) { // 鉴权成功
            printf("登录成功!\n");
            break;
        }
        wrongCount++;
        if(wrongCount == 3) {
            printf("错误3次，已关闭客户端！\n");
            return 0;
        }
    }

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

