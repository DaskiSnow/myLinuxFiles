#include <func.h>
#include <shadow.h>
#include <crypt.h>
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

    // 验证
    if(strcmp(sp->sp_pwdp, crypt(password, salt)) == 0) {
        return 1; // 返回1代表正确
    }
    else {
        return 0; // 返回0代表错误
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
