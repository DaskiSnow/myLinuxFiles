#include "head.h"

// 功能：获取用户输入的username和passwd，发送给服务端，接收鉴权结果
// 传入传出参数：is_authenticated: 0-失败 1-成功
//返回值：0-登录成功 -1-登录失败
int login(int sfd, char* username, int len1, char* passwd, int len2) {
    int is_authenticated = 0;
    int wrongCount = 0; // 登录出错次数
    while(is_authenticated == 0) { // TODO: 封装成函数，并解决退出问题
        memset(username, 0, len1);
        memset(passwd, 0, len2);

        // 用户登录
        printf("输入用户名:");
        fflush(stdout);
        read(STDIN_FILENO, username, len1);
        username[strlen(username)-1] = '\0';
        printf("输入密码:");
        fflush(stdout);
        read(STDIN_FILENO, passwd, len2);
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
            return 0;
            break;
        }
        wrongCount++;
        if(wrongCount == 3) { // 三次失败
            printf("错误3次，已关闭客户端！\n");
            return -1;
        }
    }
    return 0;
}

