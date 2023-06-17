#include "head.h"
int makeWorker(int workerNum,workerdata_t * workerdataArr){
    pid_t pid;
    for(int i = 0; i < workerNum; ++i){
        pid = fork();
        if(pid == 0){
            // 只有子进程能进入
            while(1){
                sleep(1);
            }
            // 让这个if语句块永远无法离开
        }
        // 只有父进程会调用
        workerdataArr[i].pid = pid;
        workerdataArr[i].status = FREE;
        printf("worker %d, pid = %d\n", i, pid);
    }
    return 0;
}
