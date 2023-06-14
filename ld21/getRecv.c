#include <func.h>

// 首先根据域名获取ip地址（端口号固定为80）
// 然后使用connect建立连接
// 发送query当中的内容给服务端
// 最后获取服务端回复并输出。
int main(int argc, char* argv[])
{
    const char query[] ="GET / HTTP/1.0\r\n"
                        "Host: www.baidu.com\r\n"
                        "\r\n";
    const char hostname[] = "www.baidu.com";

    // 根据域名获取IP地址
    struct hostent *phost;
    phost = gethostbyname(hostname);
    char str_ip[128] = {0};
    inet_ntop(phost->h_addrtype, phost->h_addr_list[0], str_ip, sizeof(str_ip));
    // printf("%s\n", str_ip);

    // 创建套接字, 并定义和初始化socket地址结构
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "socket");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = inet_addr(str_ip); //test

    // 客户端发起连接
    int ret = connect(sfd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "connect");

    // 发送query的内容
    ssize_t send_ret;
    send_ret = send(sfd, query, sizeof(query), 0);
    ERROR_CHECK(send_ret, -1, "send");

    // 接收回复
    char buf[10000] = {0};
    ssize_t recv_ret;
    recv_ret = recv(sfd, buf, sizeof(buf), 0);
    ERROR_CHECK(recv_ret, -1, "recv");
    
    // 打印回复
    printf("来自服务端的回复：\n%s\n", buf);

    return 0;
}

