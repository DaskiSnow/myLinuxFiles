#include <func.h>
// 编写两个程序，一个是客户端另一个是服务端，
// 它们通过tcp连接进行即时聊天。

int main(int argc, char* argv[])
{
    // ./clientChat 127.0.0.1 16888
    ARGS_CHECK(argc, 3);

    // 创建监听套接字，并初始化socket地址结构
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "socket");
    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(atoi(argv[2]));
    serAddr.sin_addr.s_addr = inet_addr(argv[1]);

    // 客户端发起连接
    int ret_connect = connect(sfd, (struct sockaddr *)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret_connect, -1, "connect");

    // select
    char buf[2048];
    fd_set rdset;
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sfd, &rdset);
        select(sfd + 1, &rdset, NULL, NULL, NULL);
        if(FD_ISSET(STDIN_FILENO, &rdset)) { // 发消息
            memset(buf, 0, sizeof(buf));
            ssize_t ret = read(STDIN_FILENO, buf, sizeof(buf));
            ERROR_CHECK(ret, -1, "read");
            if(ret == 0) { // 表明需要关闭
                printf("Closing!\n");
                break;
            }
            ret = write(sfd, buf, strlen(buf));
            ERROR_CHECK(ret, -1, "write");
        }
        if(FD_ISSET(sfd, &rdset)) { // 收消息
            memset(buf, 0, sizeof(buf));
            ssize_t ret = read(sfd, buf, sizeof(buf));
            ERROR_CHECK(ret, -1, "read");
            if(ret == 0) { //说明对端关闭
                printf("Closing!\n");
                break;
            }
            printf("Server say: %s\n", buf);
        }
    }

    // 关闭套接字
    close(sfd);

    return 0;
}

