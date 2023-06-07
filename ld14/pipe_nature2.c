#include <func.h>

// 验证匿名管道 是否发生写阻塞
int main(int argc, char* argv[])
{
    // 创建匿名管道
    int fds[2];
    pipe(fds);

    char buf[20] = {0};
    // 创建父子进程, 父读端，子写端 
    if(fork()){
        close(fds[1]);
        
        // 父读一会，睡一会，再读
        while(1) {
            int rret = read(fds[0], buf, sizeof(buf)-1);
            ERROR_CHECK(rret, -1, "child read");
            puts(buf);
            sleep(1);
        }
        wait(NULL);
        return 0;
    }
    else{
        close(fds[0]);

        int writeNum = 0; // 子每写入一次都会加1
        // 子一直写
        while(1){
            write(fds[1], "Message from child.\n", 19);
            printf("Child: writeNum = %d.\n", ++writeNum);
        }
        return 0;
    }
}

