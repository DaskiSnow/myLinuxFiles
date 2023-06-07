#include <func.h>

// 一种：read 阻塞时，处理完信号后，会导致read直接返回，而非恢复阻塞；
// 另一种：恢复阻塞（重新启动系统调用）
void handler(int signum) {
    printf("Handler.\n");
}

int main(int argc, char* argv[])
{
    int fds[2];
    pipe(fds);
    char buf[2048] = {0};
    if(fork()) { // 父进程,父读,子写
        // 注册信号
        signal(SIGINT, handler);
        close(fds[1]);

        ssize_t rret = read(fds[0], buf, sizeof(buf));
        ERROR_CHECK(rret, -1, "read");
        printf("rret = %ld\n", rret);
        return 0;
    }
    else { // 子进程
        close(fds[0]);
        while(1);
        return 0;
    }
}

