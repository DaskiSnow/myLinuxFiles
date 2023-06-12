#include <func.h>

typedef struct shareRes_s {
    long ticketNum;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareRes_t;

void* threadFun1(void* arg) {
    long mySell = 0;
    shareRes_t* pshared = (shareRes_t *)arg;
    while(1) {
        pthread_mutex_lock(&pshared->mutex);
        if(pshared->ticketNum <= 0) {
            pthread_exit((void*)mySell);
        }
        // 临界区
        pshared->ticketNum--;
        mySell++;
        printf("thread 1 : ticketNum = %ld, mySell = %ld\n", pshared->ticketNum, mySell);
        pthread_mutex_unlock(&pshared->mutex);
        // 临界区end
    }
    pthread_exit(NULL);
}

void* threadFun2(void* arg) {
    long mySell = 0;
    shareRes_t* pshared = (shareRes_t *)arg;
    while(1) {
        pthread_mutex_lock(&pshared->mutex);
        if(pshared->ticketNum <= 0) {
            pthread_exit((void*)mySell);
        }
        // 临界区
        pshared->ticketNum--;
        mySell++;
        printf("thread 2 : ticketNum = %ld, mySell = %ld\n", pshared->ticketNum, mySell);
        pthread_mutex_unlock(&pshared->mutex);
        // 临界区end
    }
    pthread_exit(NULL);
}



int main(int argc, char* argv[])
{
    // 定义结构体、初始化锁、条件变量、互斥资源（flag）
    shareRes_t shared;
    int ret = pthread_mutex_init(&shared.mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");
    ret = pthread_cond_init(&shared.cond, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_cond_init");
    shared.ticketNum = 100;

    // 创建子线程
    pthread_t tid1, tid2;
    ret = pthread_create(&tid1, NULL, threadFun1, &shared);
    THREAD_ERROR_CHECK(ret, "pthread_create 1");
    ret = pthread_create(&tid2, NULL, threadFun2, &shared);
    THREAD_ERROR_CHECK(ret, "pthread_create 2");

    // 等待子线程，并获取子线程返回值
    void *temp1, *temp2;
    pthread_join(tid1, &temp1);
    pthread_join(tid2, &temp2);
    long sell1, sell2;
    sell1 = (long)temp1;
    sell2 = (long)temp2;

    // 摧毁锁、条件变量
    pthread_mutex_destroy(&shared.mutex);    
    pthread_cond_destroy(&shared.cond);    

    // 打印销售额
    printf("sell1 = %ld\n", sell1);
    printf("sell2 = %ld\n", sell2);

    return 0;
}

