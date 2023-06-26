#include "threadPool.h"
void getSalt(char* salt, char* cryptPasswd) {
    int i, j;
    for(i = 0, j = 0; cryptPasswd[i] && j != 3; i++) {
        if(cryptPasswd[i] == '$') j++; 
    }
    strncpy(salt, cryptPasswd, i-1);
}

// 服务端的用户的验证
// 输入用户名和明文密码，返回0-失败 1-成功
int justify(const char* username, const char* password) {
    struct spwd* sp;
    char salt[512] = {0};

    sp = getspnam(username);
    if(sp == NULL) {
        perror("getspnam");
        return 0; // 根据用户名查询时错误
    }

    getSalt(salt, sp->sp_pwdp);

    printf("cryptPasswd:%s",crypt(password, salt));
    // 验证
    if(strcmp(sp->sp_pwdp, crypt(password, salt)) == 0) {
        return 1; // 返回1代表正确
    }
    else {
        return 0; // 返回0代表错误
    }
}

// 功能：接收用户名和密码，并返回验证结果
// 返回值：-1-失败 0-成功
int authenticate(int netfd, char* username, int len1, char* passwd, int len2) {
    int wrongCount = 0; // 记录用户错误次数，三次错误则返回-1
    while(1) { 
        // 接收登录信息，返回鉴权结果
        int length;
        memset(username, 0, len1);
        memset(passwd, 0, len2);
        recvn(netfd, &length, sizeof(int));
        recvn(netfd, username, length);
        recvn(netfd, &length, sizeof(int));
        recvn(netfd, passwd, length);
        printf("username=%s,passwd=%s\n", username, passwd);
        int is_authenticated = justify(username, passwd); // 0-失败 1-成功
        send(netfd, &is_authenticated, sizeof(int), MSG_NOSIGNAL);
        if(is_authenticated == 0) { // 鉴权失败，关闭链接
            printf("有一个用户登录失败, 等待再次登录\n");
            wrongCount++;
            if(wrongCount == 3) {
            return -1;
        }
            continue; // 鉴权失败
        }
        else { // 鉴权成功
            printf("有一个用户登录成功\n");
            return 0;
        }
    }
    
}

//test
//int main(int argc, char* argv[])
//{
//    // ./crypt username passwd
//    int ret = justify(argv[1], argv[2]);
//    printf("ret = %d\n", ret);
//    return 0;
//}
//
