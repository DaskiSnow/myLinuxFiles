#include "head.h"

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
    else if(strcmp(opStr, "mkdir") == 0) {
        *res = MKDIR;
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

    // 使用strtok_r切割buf，获取token
    char *token;
    char *saveptr; // 保存剩余串的指针
    token = strtok_r(buf, " ", &saveptr); // 获取操作token

    /*下面这段代码是为了避免token中包含换行符, 下同理*/
    char* ptr = NULL;
    if(token != NULL) {
        ptr = strchr(token, '\n');  // 查找第一个换行符
        if(ptr && *ptr == '\n') *ptr = '\0';
    }
    /*end*/

    if(opStrToInteger(token, &pOpVar->op) != 0){ // 转换成操作数
        return -1; // 输入的操作非法
    }
    // 获取参数token
    int arg_index = 0;
    token = strtok_r(NULL, " \n", &saveptr); 
    if(token != NULL) {
        ptr = strchr(token, '\n');  // 查找第一个换行符
        if(ptr && *ptr == '\n') *ptr = '\0';
    }
    while(token != NULL) {
        strcpy(pOpVar->argv[arg_index], token); // 存储参数字符串
        token = strtok_r(NULL, " \n", &saveptr); 
        if(token != NULL) {
            ptr = strchr(token, '\n');  // 查找第一个换行符
            if(ptr && *ptr == '\n') *ptr = '\0';
        }
        arg_index++;
    }
    pOpVar->argc = arg_index; // 参数个数
    // TODO:检查参数个数是否正确
    return 0;
}

// 发送命令
int sendcmd(int netfd, opVar_t opVar) {
    send(netfd, &opVar.op, sizeof(int), MSG_NOSIGNAL);
    send(netfd, &opVar.argc, sizeof(int), MSG_NOSIGNAL);
    for(int i = 0; i < opVar.argc; i++) {
        send(netfd, opVar.argv[i], 128, MSG_NOSIGNAL);
    }
    return 0;
}

// for test
//int main(int argc, char* argv[])
//{
//    opVar_t opVar;
//    initOpvar(&opVar);
//    int ret = readOp(&opVar);
//    if(ret == -1) {
//        printf("传入的命令非法\n");
//    }
//    printf("opVar.op = %d; opVar.argc = %d ; argv[0] = %s; argv[1] = %s\n", 
//           opVar.op, opVar.argc,opVar.argv[0], opVar.argv[1]);
//}
