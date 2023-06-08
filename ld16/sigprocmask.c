#include <func.h>
// 通过sigprocmask阻塞2号信号，睡眠5秒后，解除阻塞，2号信号得到执行；
// 在睡眠后，解除阻塞之前，通过sigpending检测是否有信号挂起。

int main(int argc, char* argv[])
{
    // 设置mask集合
    sigset_t mask_set;
    sigemptyset(&mask_set);
    sigaddset(&mask_set, SIGINT);

    // 设置全程阻塞
    sigset_t oldset; // 存储旧mask集合
    sigprocmask(SIG_BLOCK, &mask_set, &oldset);

    sleep(5);
    printf("\nSleep over!\n");
    
    // 检测SIGINT是否进入未决集合
    sigset_t pending_set;
    sigemptyset(&pending_set);
    sigpending(&pending_set);
    if(sigismember(&pending_set, SIGINT)){
        printf("\nSIGINT is pending.\n");
    }
    else{
        printf("\nSIGINT is not pending.\n");
    }


    // 解除阻塞，还原到oldset集合
    sigprocmask(SIG_SETMASK, &oldset, NULL);
    return 0;
}

