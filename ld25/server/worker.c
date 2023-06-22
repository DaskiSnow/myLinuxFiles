#include "threadPool.h"

int makeWorker(threadPool_t* pthreadPool) {
    for(int i = 0; i < pthreadPool->workerNum; i++) {
        pthread_create(&pthreadPool->tidArr[i], NULL, threadFunc, pthreadPool);
    } 
    return 0;
}

void* threadFunc(void* arg) {
    threadPool_t *pthreadPool = (threadPool_t *)arg;
    while(1) {
        // 取任务
        pthread_mutex_lock(&pthreadPool->taskQueue.mutex);
        while(pthreadPool->exitFlag == 0 && pthreadPool->taskQueue.queueSize <= 0) {
            pthread_cond_wait(&pthreadPool->taskQueue.cond, &pthreadPool->taskQueue.mutex);
        }
        // 检测到关闭标志
        if(pthreadPool->exitFlag != 0) {
            printf("A child thread is going to exit!\n");
            pthread_mutex_unlock(&pthreadPool->taskQueue.mutex); //不能带锁终止
            pthread_exit(NULL);
        }
        printf("A child get a netfd!\n");
        int netfd = pthreadPool->taskQueue.pFront->netfd;
        deQueue(&pthreadPool->taskQueue);
        pthread_mutex_unlock(&pthreadPool->taskQueue.mutex);

        // 不断处理某个Client的请求，直至该客户端关闭连接
        while(1) {
            // 获取Client发来的命令
            opVar_t opVar;
            initOpVar(&opVar);
            int rret = recvcmd(netfd, &opVar);
            // printf("op = %d ; argc = %d ; argv[0] = %s ; argv[1] = %s\n",
            //       opVar.op, opVar.argc, opVar.argv[0], opVar.argv[1]);
            if(rret == -1) {
                printf("一个客户端粗暴退出\n");
                close(netfd);
                printf("一个子线程恢复空闲\n");
                break;
            }
            // 根据不同命令进行返回
            if(opVar.op == QUIT) {
                printf("一个客户端正常退出\n");
                close(netfd);
                printf("一个子线程恢复空闲\n");
                break;
            }
            else if(opVar.op == CD) {

            }
            else if(opVar.op == LS) {

            }
            else if(opVar.op == PUTS) {

            }
            else if(opVar.op == GETS) {

            }
            else if(opVar.op == REMOVE) {

            }
            else if(opVar.op == PWD) {

            }

            // TODO:cd、ls ...操作，返回字符串
            // 传输文件
            transfile(netfd);
            printf("传送完一个文件\n");
            // 恢复空闲

        }

    }
}

