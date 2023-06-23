#include <func.h>
typedef struct train_s {
    int length;
    char data[10000];
} train_t;

enum {
    CD,
    LS,
    PUTS,
    GETS,
    REMOVE,
    PWD,
    MKDIR,
    QUIT,
    LOGIN
};

typedef struct opVar_s {
    int op;         // 操作
    int argc;       // 参数个数
    char* argv[10]; // 参数token集合, 需要预先分配空间
} opVar_t;

int recvn(int netfd, void* buf, int length);
int recvfile(int netfd); 
int epollAdd(int epfd, int fd);
int epollDel(int epfd, int fd);
void initOpvar(opVar_t *pOpvar);
void destroyOpvar(opVar_t *pOpvar);
int readOp(opVar_t* pOpVar);
int opStrToInteger(char* opStr, int* res);
int sendcmd(int netfd, opVar_t opVar);
int login(int sfd, char* username, int len1, char* passwd, int len2);
