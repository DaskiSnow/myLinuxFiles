#include <func.h>

void deamon(void);

int main(int argc, char* argv[])
{
    deamon();
    return 0;
}

void deamon(void) {
    if(fork()!=0) {
        // 关闭父进程
        exit(1);
    }
    
    // 子进程代码
    // 新建会话、转换到根目录、文件创建掩码置0、关闭所有文件对象
    setsid();
    chdir("/");
    umask(0);
    for(int i = 0; i < 3; i++) close(i);
    while(1);
}
