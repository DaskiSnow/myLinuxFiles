#include "threadPool.h"

// 小火车
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
    }
    // 发送长度为0的火车，表明结束传送
    train.length = 0;
    send(netfd, &train.length, sizeof(int), MSG_NOSIGNAL);
    munmap(p, filesize);
    
    close(netfd);

    return 0;
}

