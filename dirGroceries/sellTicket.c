#include <func.h>

typedef struct shareRes_s {
    int ticketNum;
    pthread_mutex_t mutex;
}shareRes_t;

void* threadFun1(void* arg) {
    long mySell = 0; // 销售额
    shareRes_t *pshared = (shareRes_t *)arg;
    
    while(1) {
        while(1) {
            pthread_mutex_lock(&pshared->mutex);
            if(pshared->ticketNum <= 0) { // flag条件不满足
                pthread_mutex_unlock(&pshared->mutex);
                pthread_exit((void*)mySell); // 值传递
            } // flag条件满足
            break;
        }
        // 临界区
        pshared->ticketNum--;
        mySell++;
        pthread_mutex_unlock(&pshared->mutex);
        // 临界区end
        usleep(100);
    }
    pthread_exit(NULL);
}

void* threadFun2(void* arg) {
    long mySell = 0; // 销售额
    shareRes_t *pshared = (shareRes_t *)arg;
    
    while(1) {
        while(1) {
            pthread_mutex_lock(&pshared->mutex);
            if(pshared->ticketNum <= 0) { // flag条件不满足
                pthread_mutex_unlock(&pshared->mutex);
                pthread_exit((void*)mySell); // 值传递
            } // flag条件满足
            break;
        }
        // 临界区
        pshared->ticketNum--;
        mySell++;
        pthread_mutex_unlock(&pshared->mutex);
        // 临界区end
        usleep(100);
    }
    pthread_exit(NULL);

}

int main(void){
    // 定义结构体，初始化锁、互斥资源
    shareRes_t shared;
    shared.ticketNum = 100;
    int ret = pthread_mutex_init(&shared.mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");

    // 创建子线程
    pthread_t tid1, tid2;
    ret =pthread_create(&tid1, NULL, threadFun1, &shared);
    THREAD_ERROR_CHECK(ret, "pthread_create 1");
    ret =pthread_create(&tid2, NULL, threadFun2, &shared);
    THREAD_ERROR_CHECK(ret, "pthread_create 2");

    // 等待子线程结束
    void *temp1, *temp2;
    ret = pthread_join(tid1, &temp1);
    THREAD_ERROR_CHECK(ret, "pthread_join 1");
    ret = pthread_join(tid2, &temp2);
    THREAD_ERROR_CHECK(ret, "pthread_join 2");

    long sell1, sell2;
    sell1 = (long)temp1;
    sell2 = (long)temp2;
    printf("sell1 = %ld\n", sell1);
    printf("sell2 = %ld\n", sell2);

    // 摧毁锁
    pthread_mutex_destroy(&shared.mutex);

    return 0;
}
