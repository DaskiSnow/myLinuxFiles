#include <func.h>

// 验证匿名管道 写端先关闭，读端继续读
int main(int argc, char* argv[])
{
    // 创建匿名管道
    int fds[2];
    pipe(fds);

    char buf[2048] = {0};
    // 创建父子进程, 父读端，子写端 
    if(fork()){
        close(fds[1]);

        wait(NULL);

        ssize_t rret = read(fds[0], buf, sizeof(buf));
        printf("rret = %ld\n", rret);
        return 0;
    }
    else{
        close(fds[0]);

        close(fds[1]); // 子写端关闭
        return 0;
    }
}

