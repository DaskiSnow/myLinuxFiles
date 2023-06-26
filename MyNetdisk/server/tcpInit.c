#include <func.h>

int tcpInit(const char* ip, const char* port, int* psfd) {
    // 创建socket
    *psfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(*psfd, -1, "tcpInit");

    // 设置socket属性
    int reuse = 1;
    setsockopt(*psfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

    // 绑定ip和port
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);
    bind(*psfd, (struct sockaddr *)&addr, sizeof(addr));

    // 开启监听
    listen(*psfd, 50);

    return 0;
}

