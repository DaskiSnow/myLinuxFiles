#include <func.h>
// 使用select编写聊天室程序：
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

    // 监听sfd和标准输入
    char buf[4096] = {0};
    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sfd, &rdset);
        
        select(sfd + 1, &rdset, NULL, NULL, NULL);
        
        // 标准输入读取消息，并发到服务端
        if(FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            int ret = read(STDIN_FILENO, buf, sizeof(buf)-1);
            ERROR_CHECK(ret, -1, "read");
            if(ret == 0) { // 表明关闭客户端
                break;
            }
            ret = send(sfd, buf, strlen(buf), 0);
            ERROR_CHECK(ret, -1, "send");
        }
        
        // 收到聊天室的消息
        if(FD_ISSET(sfd, &rdset)) { 
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
    printf("客户端结束连接\n");
    close(sfd);

    return 0;
}

