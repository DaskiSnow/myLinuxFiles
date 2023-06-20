#include <func.h>
typedef struct train_s {
    int length;
    char data[10000];
} train_t;

int recvn(int netfd, void* buf, int length) {
    int total = 0;
    char *p = (char *)buf;
    while(total < length) {
        int ret = recv(netfd, p, length-total, 0);
        if(ret == 0) {
            return -1;
        }
        total += ret;
    }
    return 0;
}

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
}
