#include <func.h>

// 父进程获取子进程的信息
enum {
    FREE, 
    BUSY
};
typedef struct workerdata_s {
    pid_t pid;  // 子进程pid
    int status; // 空闲or忙碌
    int pipefd; // 父子进程的通信管道
} workerdata_t;
int makeWorker(int wokerNum, workerdata_t* workerdataArr);
int tcpInit(const char *ip, const char *port, int *psfd);
int sendfd(int sfd, int fdtosend, int indextosend);
int recvfd(int sfd, int *pfdtorecv, int *pindextorecv);
int epollAdd(int epfd, int fd);
int epollDel(int epfd, int fd);
int eventLoop(int spfd);
