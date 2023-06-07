#include <func.h>

// 测试WEXITSTATUS(status)的返回值范围
int main(int argc, char* argv[])
{
    if(fork()){ // 父进程
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            printf("Parent get return = %d\n", WEXITSTATUS(status));
        }
        return 0;
    }
    else{ // 子进程
        int ret = -5;
        printf("real return %d\n", ret);
        return ret;
    }
}

