#include <func.h>
// 使用epoll编写聊天室程序：
// 客户端和服务端使用tcp通信；
// 服务端可以处理新客户端的连接和转发消息；
// 客户端可以连入服务端并发送消息。

int main(int argc, char* argv[])
{
    // clientChatRoom_select 192.168.182.135 16888
    ARGS_CHECK(argc, 3);

    // 创建socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "socket");

    // 定义并初始化地址结构变量
    struct sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(atoi(argv[2]));
    serAddr.sin_addr.s_addr = inet_addr(argv[1]); 
    
    // 连接服务端connect
    int ret = connect(sfd, (struct sockaddr *)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret, -1, "connect");

    // 创建epoll文件对象
    int epfd = epoll_create(1);

    // 添加监听
    struct epoll_event event, evs[10];
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    event.events = EPOLLIN;
    event.data.fd = sfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    int readyNum = 0;
    char buf[4096] = {0};
    while(1) {
        int out = 0;
        readyNum = epoll_wait(epfd, evs, 10, -1);
        for(int i = 0; i < readyNum; i++) {
            if(evs[i].data.fd == STDIN_FILENO) {
                int rret = read(STDIN_FILENO, buf, sizeof(buf));
                ERROR_CHECK(ret, -1, "read");
                if(ret == 0) { // 表明关闭客户端
                    out = 1;
                    break;
                }
                ret = send(sfd, buf, strlen(buf), 0);
                ERROR_CHECK(ret, -1, "send");
            }
            else if(evs[i].data.fd == sfd) {
                memset(buf, 0, sizeof(buf));
                int ret = recv(sfd, buf, sizeof(buf), 0);
                ERROR_CHECK(ret, -1, "recv");
                if(ret == 0) { // 被踢出聊天室
                    printf("被踢出聊天室或服务端关闭了\n");
                    break;
                }
                // 打印消息
                printf("来自聊天室的消息：%s\n", buf);

            }
        }
        if(out == 1) break;
    } 
    close(sfd);
    close(epfd);
    printf("客户端结束连接\n");

    return 0;
}

