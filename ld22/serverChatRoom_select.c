#include <func.h>
// 使用select编写聊天室程序：
// 客户端和服务端使用tcp通信；
// 服务端可以处理新客户端的连接和转发消息；
// 客户端可以连入服务端并发送消息。

void printfd(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        printf("nfd[%d] = %d; ", i,arr[i]);
    }
    printf("\n");
}

void setArr(int arr[], int n, int val) {
    for(int i = 0; i < n; i++) {
        arr[i] = val;
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

    int nfd[9] = {-1}; // 存储已连接客户端的nfd
    setArr(nfd, SIZE(nfd), -1);
    // printfd(nfd,9);
    fd_set rdset;
    fd_set monitorSet;
    FD_ZERO(&rdset);
    FD_ZERO(&monitorSet);
    FD_SET(sfd, &monitorSet); // 开始时，只有sfd和STDIN_FILENO 
    FD_SET(STDIN_FILENO, &monitorSet);
    while(1) {
        memcpy(&rdset, &monitorSet, sizeof(fd_set));
        select(10, &rdset, NULL, NULL, NULL); // 假设fd不超过9
        
        // 服务端需要结束时才会触发
        if(FD_ISSET(STDIN_FILENO, &rdset)){
            char buf[128] = {0};
            int rret = read(STDIN_FILENO, buf, sizeof(buf));
            ERROR_CHECK(rret, -1, "read");
            if(rret == 0) {
                break;
            }
        }
        
        // 有客户端连接
        if(FD_ISSET(sfd, &rdset)) {
            // 定义地址结构变量，存储客户端ip和port信息
            struct sockaddr_in cliAddr;
            memset(&cliAddr, 0, sizeof(cliAddr));
            socklen_t addrlen = sizeof(cliAddr);
            
            // accept一个客户端连接
            int temp_nfd = accept(sfd, (struct sockaddr *)&cliAddr, &addrlen);
            printf("接收到一个客户端连接\n");
            // 存储nfd
            for(int i = 0; i < SIZE(nfd); i++) {
                if(nfd[i] == -1) { // 找到一个空位
                    nfd[i] = temp_nfd;
                    break;
                }
            }
            
            // 添加到监听集合
            FD_SET(temp_nfd, &monitorSet);
        }

        char buf[4096] = {0};
        // 有客户端发消息，转发该消息
        // 依次遍历nfd[]
        for(int i = 0; i < SIZE(nfd); i++) {
            if(nfd[i] == -1) continue;

            if(FD_ISSET(nfd[i], &rdset)) {
                memset(buf, 0, sizeof(buf));
                int rret = recv(nfd[i], buf, sizeof(buf)-1, 0);
                ERROR_CHECK(rret, -1, "recv");

                if(rret == 0) { // 说明该客户端已断开
                    nfd[i] = -1;
                    FD_CLR(nfd[i], &monitorSet);
                    close(nfd[i]);
                    printf("一个客户端已断开.\n");
                    continue;
                }
                // printf("收到信息:%s\n", buf);
                // 转发给其他客户端
                for(int j = 0; j < SIZE(nfd); j++) {
                    if((nfd[j] == -1) || (j == i)) continue;
                    int wret = send(nfd[j], buf, strlen(buf), 0);
                    ERROR_CHECK(wret, -1, "send");
                    printf("send: nfd = %d, buf = %s\n", nfd[j], buf);
                }
            }
        }
    }

    close(sfd);

    return 0;
}

