#include <func.h>

int my_dup2(int oldfd, int newfd);

int main(void)
{
    int oldfd = open("open.txt",O_WRONLY);
    ERROR_CHECK(oldfd, -1, "open");
    write(oldfd, "Hello ", 6);
    int newfd = 1000;
    my_dup2(oldfd, newfd);
    write(newfd, "World\n", 6);

    printf("oldfd = %d, newfd = %d\n", oldfd, newfd);
    close(newfd);
    close(oldfd);
    return 0;
}

int my_dup2(int oldfd, int newfd) {
    // 检查newfd参数
    if (newfd >= 1024) return -1;

    // 检查oldfd能否打开
    struct stat buf;
    int ret_fstat = fstat(oldfd, &buf);
    ERROR_CHECK(ret_fstat, -1, "fstat");

    // 关闭newfd
    close(newfd);  // 关闭一个不指向文件对象的文件描述符，会被系统忽略，返回0
    
    // 存储分配过的文件描述符
    int opened[1024] = {-1};

    // 不断dup直到与newfd相等
    int count = 0;
    int fd_dup;
    while(1) {
        fd_dup = dup(oldfd);
        if(newfd == fd_dup || fd_dup >= 1024) break;
        opened[count++] = fd_dup;
    }

    // 关闭多余打开的文件描述符
    for(int i = 0; i < count; i++) {
        close(opened[i]);
    }

    if(fd_dup >= 1024) return -1;

    return fd_dup;
}


