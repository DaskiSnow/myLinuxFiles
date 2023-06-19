#include <func.h>
// 用于让父进程知道每个子进程的信息
enum {
    FREE,
    BUSY
};
typedef struct workerdata_s {
    pid_t pid; //子进程的pid
    int status; //子进程是空闲还是忙碌
    int pipefd; //父进程用于和子进程通信的管道
} workerdata_t;
int makeWorker(int workerNum, workerdata_t * workerdataArr);
int tcpInit(const char *ip, const char *port, int * psockfd);
int sendfd(int sockfd, int fdtosend);
int recvfd(int sockfd, int *pfdtorecv);
int epollAdd(int epfd, int fd);
int epollDel(int epfd, int fd);
int eventLoop(int sockfd);
