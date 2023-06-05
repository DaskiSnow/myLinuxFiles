#include <func.h>

// 创建一个孤儿进程
int main(int argc, char* argv[])
{
    pid_t pid = fork();
    
    if(pid == 0) {
        printf("Child. Be about to be orphan.\n");
        while(1);
    }
    else{
        printf("Parent.\n");
    }
    return 0;
}

