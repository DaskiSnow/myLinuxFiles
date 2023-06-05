#include <func.h>

// 创建一个僵尸进程
int main(int argc, char* argv[])
{
    pid_t pid = fork();

    if(pid == 0) {
        printf("Child. To be over.\n");
    }
    else{
        printf("Parent. No wait.\n");
        while(1);
    }
    return 0;
}

