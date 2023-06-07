#include <func.h>

// 验证匿名管道 是否发生写阻塞
// 纠正心得：注意close的位置
int main(int argc, char* argv[])
{
    // 创建匿名管道
    int fds[2];
    pipe(fds);

    char buf[4096] = {0};
    // 创建父子进程, 父读端，子写端 
    if(fork()){
        close(fds[1]);
        
        /* 父不读 */

        wait(NULL);

        close(fds[0]);

        return 0;
    }
    else{
        close(fds[0]);

        int writeNum = 0; // 子每写入一次都会加1
        while(1){
        // 子一直写
            ssize_t wret = write(fds[1], buf, 4096);
            ERROR_CHECK(wret, -1, "write");
            printf("Child: writeNum = %d.\n", ++writeNum);
        }
        close(fds[1]);
        return 0;
    }
}

