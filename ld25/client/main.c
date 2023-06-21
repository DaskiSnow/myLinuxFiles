#include <func.h>
#include "head.h"

enum {
    CD,
    LS,
    PUTS,
    GETS,
    REMOVE,
    PWD,
    QUIT
};

typedef struct opVar_s {
    int op;         // 操作
    char* argv[10]; // 参数token集合, 需要预先分配空间
} opVar_t;

// 功能：为agrv分配空间
void initOpvar(opVar_t *pOpvar) {
    for(int i = 0; i < 10; i++) {
        pOpvar->argv[i] = (char*)calloc(1, 128);
    }
}

// 功能：释放argv的空间
void destroyOpvar(opVar_t *pOpvar) {
    for(int i = 0; i < 10; i++) {
        free(pOpvar->argv[i]);
    }

}
// 功能：将操作字符串转成对应的整型数
// 返回值：-1-失败 0-成功 
int opStrToInteger(char* opStr, int* res) {
    if(strcmp(opStr, "cd") == 0) {
        *res = CD;
    }
    else if(strcmp(opStr, "ls") == 0) {
        *res = LS;
    }
    else if(strcmp(opStr, "puts") == 0) {
        *res = PUTS;
    }
    else if(strcmp(opStr, "gets") == 0) {
        *res = GETS;
    }
    else if(strcmp(opStr, "remove") == 0) {
        *res = REMOVE;
    }
    else if(strcmp(opStr, "pwd") == 0) {
        *res = PWD;
    }
    else if(strcmp(opStr, "quit") == 0) {
        *res = QUIT;
    }
    else { // 输入不合法
        return -1; // 执行失败
    }
    return 0; // 执行成功
}

// 读取STDIN内容的操作命令，并存储在op中
// 返回值 -1-失败 0-成功
int readOp(opVar_t* pOpVar) {
    char buf[1024] = {0}; // 存储用户输入的内容
    int rret = read(STDIN_FILENO, buf, sizeof(buf));
    ERROR_CHECK(rret, -1, "read STDIN_FILENO");
    printf("buf = %s\n", buf);

    // 使用strtok_r切割buf，获取token
    char *token;
    char *saveptr; // 保存剩余串的指针
    memset(pOpVar, 0, sizeof(opVar_t));
    token = strtok_r(buf, " ", &saveptr); // 获取操作token
    printf("op token = %s\n", token);
    if(opStrToInteger(token, &pOpVar->op) != 0){ // 转换成操作数
        return -1; // 输入的操作非法
    } 
    printf("op integer = %d\n", pOpVar->op);
    // 获取参数token
    int arg_index = 0;
    while(token != NULL) {
        token = strtok_r(NULL, " ", &saveptr); // 操作所需的参数
        if(token[0] == '\0') {
            printf("当前token第一个为空字符\n");
            printf("Token: %s\n", token); 
        }
        if(token[0] != '\0') {
            printf("Token: %s\n", token); 
            strcpy(pOpVar->argv[arg_index], token);
            arg_index++;
        }
    }
    // TODO:检查参数个数是否正确
    return 0;
} 
// for test
int main(int argc, char* argv[])
{
    opVar_t opVar;
    initOpvar(&opVar);
    readOp(&opVar);
}
//int main(int argc, char* argv[])
//{
//    // ./client serIp serPort
//    int sfd = socket(AF_INET, SOCK_STREAM, 0);
//    ERROR_CHECK(sfd, -1, "socket");
//
//    struct sockaddr_in addr;
//    addr.sin_family = AF_INET;
//    addr.sin_port = htons(atoi(argv[2]));
//    addr.sin_addr.s_addr = inet_addr(argv[1]);
//    int ret = connect(sfd, (struct sockaddr *)&addr, sizeof(addr));
//    ERROR_CHECK(ret, -1, "connect");
//
//    // 创建epoll文件对象，并增加STDIN和的sfd监听
//    int epfd = epoll_create(1);    
//    epollAdd(epfd, STDIN_FILENO);
//    epollAdd(epfd, sfd);
//
//    // 开启监听
//    struct epoll_event evs[2];
//    while(1) {
//        int readyNum = epoll_wait(epfd, evs, SIZE(evs), -1);
//        for(int i = 0; i < readyNum; i++) {
//            if(evs[i].data.fd == STDIN_FILENO) { // 来自用户输入
//                // TODO: cd操作
//                // TODO: ls操作
//                // TODO: puts 将本地文件上传至服务器
//                // TODO: gets 文件名 下载服务器文件到本地
//                // TODO: remove 删除服务器上文件
//                // TODO: pwd 显示目前所在路径
//                // TODO: 其他命令...
//                // TODO: 无效命令不响应
//                // TODO: 关闭连接
//            }
//            else if(evs[i].data.fd == sfd) { // 来自服务端的回复或传输内容
//                // TODO: 服务端返回操作后的字符串，客户端打印
//                // TODO: 服务端传输文件，客户端接收
//
//                // 接收文件
//                printf("准备接收文件...\n");
//                recvfile(sfd);
//                printf("接收完毕！\n");
//            }
//        }
//    }
//    close(sfd);
//
//    return 0;
//}

