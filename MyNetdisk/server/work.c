#include "headServer.h"

int makeWorker(threadPool_t* pthreadPool) {
    for(int i = 0; i < pthreadPool->workerNum; i++) {
        pthread_create(&pthreadPool->tidArr[i], NULL, threadFunc, pthreadPool);
    } 
    return 0;
}

void* threadFunc(void* arg) {
    threadPool_t *pthreadPool = (threadPool_t *)arg; 
    
    // 获取所属进程的工作目录
    char realPath[1024] = {0};
    getcwd(realPath, sizeof(realPath));
    char path[2048] = {0};
    getcwd(path, sizeof(path));

    while(1) {
        // 子线程等待任务
        pthread_mutex_lock(&pthreadPool->lkQueue.mutex);
        while(pthreadPool->exitFlag == 0 && pthreadPool->lkQueue.queueSize <= 0) {
            pthread_cond_wait(&pthreadPool->lkQueue.cond, &pthreadPool->lkQueue.mutex);
        }

        // 被唤醒，检测到关闭标志
        if(pthreadPool->exitFlag != 0) {
            printf("A child thread is going to exit!\n");
            pthread_mutex_unlock(&pthreadPool->lkQueue.mutex); //不能带锁终止
            pthread_exit(NULL);
        }

        // 子线程获得任务
        printf("A child get a netfd!\n");
        int netfd = pthreadPool->lkQueue.pFront->netfd;
        deQueue(&pthreadPool->lkQueue);
        pthread_mutex_unlock(&pthreadPool->lkQueue.mutex);

        // 先接收用户名和token值
        
        // 验证token, 成功则向下执行，失败则关闭连接并continue
        
        char username[1024] = {0};
        char passwd[1024] = {0};
        int ret_authen = authenticate(netfd, username, sizeof(username) ,passwd, sizeof(passwd)); //登录成功返回0, 错误三次返回1
        if(ret_authen == -1) {
            printf("用户[%s]鉴权失败，断开连接！\n", username);
            close(netfd);
            continue;
        }

        /* 子进程处理GETS/PUTS任务 */
        // (封装)接收操作信息、当前目录信息、文件大小、文件名信息、MD5(包括后缀)
        
        // if(客户端上传操作), 新建同名文件(包括后缀)，接收文件内容
        

        // if(客户端下载操作), 接收文件已下载的字节数、文件虚拟路径信息、
        // 根据用户名和路径(包含文件名)在数据库获取文件的MD5
        // 根据MD5找到物理文件，利用mmap实现断点续传
        
        
        

    }
}
