#include "headServer.h"

int initThreadPool(threadPool_t* pthreadPool, int workerNum, MYSQL* db) {
    pthreadPool->tidArr = (pthread_t *)calloc(workerNum, sizeof(pthread_t));
    pthreadPool->workerNum = workerNum;
    initQueue(&pthreadPool->lkQueue);
    pthreadPool->exitFlag = 0;
    
    // 数据库初始化并连接
    char* host = "localhost";
    char* user = "root";
    char* passwd = "1688";
    char* database = "neydisk";
    pthreadPool->db = dbInit(host, user, passwd, database);
    if(pthreadPool->db == NULL) {
        fprintf(stderr, "dbInit failed!\n");
        return -1;
    }
    return 0;
}
