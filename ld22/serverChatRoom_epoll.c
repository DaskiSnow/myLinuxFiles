#include <func.h>
// 使用epoll编写聊天室程序：
// 客户端和服务端使用tcp通信；
// 服务端可以处理新客户端的连接和转发消息；
// 客户端可以连入服务端并发送消息。

typedef struct client_s{
    int nfd;  
    time_t time_la; // 最后依次活跃的时间
}client_t;

void printfd(client_t arr[], int n) {
    for(int i = 0; i < n; i++) {
        printf("nfd[%d] = %d; ", i,arr[i].nfd);
    }
    printf("\n");
}

void setFd(client_t client_arr[], int n, int val) {
    for(int i = 0; i < n; i++) {
        client_arr[i].nfd = val;
    }
}


int main(int argc, char* argv[])
{
    // serverChatRoom_select 0.0.0.0 16888
    ARGS_CHECK(argc, 3);

    // 创建socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "socket");

    // 定义并初始化地址结构变量
    struct sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(atoi(argv[2]));
    serAddr.sin_addr.s_addr = inet_addr(argv[1]); 
    
    // 设置socket属性
    int reuse = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

    // 赋予socket IP 和 端口
    int ret = bind(sfd, (struct sockaddr *)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret, -1, "bind");

    // 改造成 listen socket
    ret = listen(sfd, 50);
    ERROR_CHECK(ret, -1, "listen");

    client_t clientArr[9]; // 存储已连接客户端的nfd和time_la
    setFd(clientArr, SIZE(clientArr), -1);
    // printfd(clientArr,9);
    
    // 创建epoll文件对象
    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");
    
    // 添加监听
    struct epoll_event event, evs[10];
    memset(&event, 0, sizeof(event));
    memset(&evs, 0, sizeof(evs));
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    event.events = EPOLLIN;
    event.data.fd = sfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    int readyNum = 0;
    while(1) {
        int out = 0; // 标志是否退出
        readyNum = epoll_wait(epfd, evs, 10, -1);
        for(int i = 0; i < readyNum; i++) {
            // printf("readyNum = %d\n", readyNum);
            if(evs[i].data.fd == STDIN_FILENO){
                char buf[128] = {0};
                int rret = read(STDIN_FILENO, buf, sizeof(buf));
                ERROR_CHECK(rret, -1, "read");
                if(rret == 0) {
                    out = 1;
                    break;
                }
            }
            else if(evs[i].data.fd == sfd) {
                // 定义地址结构变量，存储客户端ip和port信息
                struct sockaddr_in cliAddr;
                memset(&cliAddr, 0, sizeof(cliAddr));
                socklen_t addrlen = sizeof(cliAddr);

                // accept一个客户端连接
                int temp_nfd = accept(sfd, (struct sockaddr *)&cliAddr, &addrlen);
                printf("接收到一个客户端连接\n");

                // 存储nfd
                for(int j = 0; j < SIZE(clientArr); j++) {
                    if(clientArr[j].nfd == -1) { // 找到一个空位
                        clientArr[j].nfd = temp_nfd;
                        break;
                    }
                }
                // 添加到监听结合
                event.events = EPOLLIN;
                event.data.fd = temp_nfd;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, temp_nfd, &event);
                ERROR_CHECK(ret, -1, "epoll_ctl");
            }
            char buf[4096] = {0};
            // 有客户端发消息，转发该消息
            // 依次遍历nfd[]
            for(int j = 0; j < SIZE(clientArr); j++) {
                if(clientArr[j].nfd == -1) continue;

                if(evs[i].data.fd == clientArr[j].nfd) {
                    printf("有客户端发消息。\n");
                    memset(buf, 0, sizeof(buf));
                    int rret = recv(clientArr[j].nfd, buf, sizeof(buf)-1, 0);
                    ERROR_CHECK(rret, -1, "recv");

                    if(rret == 0) { // 说明该客户端已断开
                        clientArr[j].nfd = -1;
                        epoll_ctl(epfd, EPOLL_CTL_DEL, clientArr[i].nfd, NULL);
                        close(clientArr[j].nfd);
                        printf("一个客户端已断开.\n");
                        continue;
                    }
                    // 转发给其他客户端
                    for(int k = 0; k < SIZE(clientArr); k++) {
                        if((clientArr[k].nfd == -1) || (k == j)) continue;
                        int wret = send(clientArr[k].nfd, buf, strlen(buf), 0);
                        ERROR_CHECK(wret, -1, "send");
                        printf("send: clientArr[k].nfd = %d, buf = %s\n", clientArr[k].nfd, buf);
                    }
                }
            }

        }
        if(out == 1) break;
    }
    close(sfd);

    return 0;
}

