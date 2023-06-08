#include <func.h>

// 测试一下主线程打开文件以后，子线程能否通过文件描述符访问同一个文件对象？
// 如果某个线程执行close之后会怎么样？

void* thread_fun(void* arg) {
    long fd = (long)arg;

    char buf[2048] = {0};
    ssize_t rret = read(fd, buf, sizeof(buf)-1);
    ERROR_CHECK(rret, -1, "child read");

    printf("Child. fd = %ld, buf = %s\n", fd, buf);
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    long fd = open("temp.txt", O_RDWR | O_TRUNC | O_CREAT, 0664);
    ERROR_CHECK(fd, -1, "open");
    printf("Main. fd = %ld\n", fd);

    ssize_t wret = write(fd, "Main write.", 11);
    ERROR_CHECK(wret, -1, "main write");
    lseek(fd, SEEK_SET, 0);  // 将读写指针重置到开头

    // 创建子线程
    pthread_t tid;
    pthread_create(&tid, NULL, thread_fun, (void*)fd); // 值传递fd

    // 等待子线程结束
    pthread_join(tid, NULL);

    close(fd);
    return 0;
}

