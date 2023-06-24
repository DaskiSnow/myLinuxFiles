#include "head.h"

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

//  小火车接收，显示进度条
int recvfile(int netfd) {
    // 获取文件名
    char filename[1024] = {0};
    int length;
    recvn(netfd, &length, sizeof(int));
    recvn(netfd, &filename, length);

    // 根据文件名创建文件
    int fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
    ERROR_CHECK(fd, -1, "open");

    // 获取文件大小
    off_t filesize;
    recvn(netfd, &length, sizeof(length));
    recvn(netfd, &filesize, length);

    // 获取文件内容 
    char buf[10000];
    off_t cursize = 0;
    off_t slice = filesize / 10000;
    off_t lastsize = 0; // 上一次printf时已发送的长度
    while(1) {
        recvn(netfd, &length, sizeof(length));
        if(length == 0) { // 收到length=0的小火车，说明传送完毕
            // printf("收到退出信号火车头length = %d\n", length);
            break;
        }
        memset(buf, 0, sizeof(buf));
        recvn(netfd, buf, length);
        cursize += length;
        if(cursize - lastsize >= slice) {
            printf("%5.2lf%%\r", 100.00 * cursize / filesize);
            fflush(stdout);
            lastsize = cursize;
        }
        write(fd, buf, length);
    }
    printf("100.00%%\n");
    close(fd);
    return 0;
}
