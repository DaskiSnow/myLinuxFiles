#include <func.h>

int main(int argc, char* argv[])
{
    printf("uid = %d, gid = %d\n",getuid(),getgid());
    printf("euid = %d, egid = %d\n",geteuid(),getegid());
    while(1){ // 死循环保持进程存在
    }
    return 0;
}

