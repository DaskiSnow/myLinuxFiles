#include <func.h>

// 验证匿名管道 读端先关闭，写端继续写
int main(int argc, char* argv[])
{
    // 创建匿名管道
    int fds[2];
    pipe(fds);

    char buf[2048] = {0};
    // 创建父子进程, 父读端，子写端 
    if(fork()){
        close(fds[1]);

        close(fds[0]); //关闭读端
        wait(NULL);
        return 0;
    }
    else{
        close(fds[0]);

        sleep(5); // 保证读端关闭了
        while(1) {
            int wret = write(fds[1], "Message from child.\n", 19);
            ERROR_CHECK(wret, -1, "write");
            printf("Child write!\n");
        }
        return 0;
    }
}

