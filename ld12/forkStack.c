//forkStack.c
#include <func.h>

int main(void)
{
    // 父子进程中的变量包括其地址是一致的
    pid_t pid = fork();
    int i = 0;
    if(pid == 0) {
       puts("child");
       printf("child i = %d, &i = %p\n", i, &i);
       i++;
       printf("child i = %d, &i = %p\n", i, &i);
    }
    else {
        puts("parent");
        printf("parent i = %d, &i = %p\n",i, &i);
        sleep(2);
        printf("parent i = %d, &i = %p\n",i ,&i); // 子进程会拷贝父进程的内容，但是修改的内容会相互独立
    }
    return 0;
}

