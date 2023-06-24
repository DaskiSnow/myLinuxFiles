#include "threadPool.h"

int recvn(int netfd, void* buf, int length) {
    int total = 0;
    char *p = (char *)buf;
    while(total < length) {
        int ret = recv(netfd, p+total, length-total, 0);
        if(ret == 0) {
            return -1;
        }
        total += ret;
    }
    return 0;
}

// 接收客户端的命令
// 返回值：0-成功  -1-失败或写端关闭
int recvcmd(int netfd, opVar_t* opVar) {
    int rret = recvn(netfd, &opVar->op, sizeof(int));      //  接收操作
    recvn(netfd, &opVar->argc, sizeof(int));    //  接收参数个数
    char buf[128] = {0};
    for(int i = 0; i < opVar->argc; i++) {      // 接收argc个长度为128的字符串(参数)
        memset(buf, 0, sizeof(buf));
        recvn(netfd, buf, sizeof(buf));        
        strncpy(opVar->argv[i], buf, sizeof(buf));
    }
    if(rret == -1) {
        return -1;
    }
    return 0;
}

// 为argv分配堆空间
void initOpVar(opVar_t *pOpVar) {
    for(int i = 0; i < 10; i++) {
        pOpVar->argv[i] = (char*)calloc(1, 128);
    }
}

// 功能：释放argv的堆空间
void destroyOpVar(opVar_t *pOpVar) {
    for(int i = 0; i < 10; i++) {
        free(pOpVar->argv[i]);
    }
}

// 小火车发送文件
int transfile(int netfd) {
    char filepath[128] = "file1";
    // 先发送文件名
    train_t train;
    train.length = sizeof(filepath);
    memcpy(train.data, filepath, sizeof(filepath));
    send(netfd, &train, sizeof(int)+train.length, MSG_NOSIGNAL);

    // 获取文件大小
    struct stat statbuf;
    stat(filepath, &statbuf);
    off_t filesize = statbuf.st_size;

    // 发送文件大小
    train.length = sizeof(filesize);    
    memcpy(train.data, &filesize, sizeof(filesize));
    send(netfd, &train, sizeof(int)+train.length, MSG_NOSIGNAL);

    // 发送文件内容(利用mmap)
    int fd = open(filepath, O_RDWR);
    char *p = (char*)mmap(NULL, filesize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    off_t cursize = 0;
    while(filesize - cursize > 0) {
        if(filesize - cursize > 10000) {
            train.length = 10000;
        }    
        else {
            train.length = filesize - cursize;
        }
        send(netfd, &train.length, sizeof(int), MSG_NOSIGNAL);
        send(netfd, p+cursize, train.length, MSG_NOSIGNAL);
        cursize+=train.length;
        printf("发送了length = %d\n", train.length);
    }

    // 发送长度为0的火车，表明结束传送
    train.length = 0;
    send(netfd, &train.length, sizeof(int), MSG_NOSIGNAL);
    munmap(p, filesize);

    // 不要close(nfd)，应由子线程检测到用户端关闭才关闭

    return 0;
}

