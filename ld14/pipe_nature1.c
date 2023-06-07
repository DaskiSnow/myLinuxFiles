#include <func.h>

// 验证匿名管道 是否发生读阻塞
int main(int argc, char* argv[])
{
    // 创建匿名管道
    int fds[2];
    pipe(fds);

    char buf[4096] = {0};
    // 创建父子进程, 父读端，子写端 
    if(fork()){
        close(fds[1]);

        ssize_t rret = read(fds[0], buf, sizeof(buf)-1);
        ERROR_CHECK(rret, -1, "child read");
        puts(buf);

        wait(NULL);
        close(fds[0]);
        return 0;
    }
    else{
        close(fds[0]);

        // 子先睡一会，再写
        sleep(5);
        write(fds[1], "After 5s. Child wake up.\n", 24);

        close(fds[1]);

        return 0;
    }
}

