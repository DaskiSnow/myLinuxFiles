#include <func.h>
// 尝试使用2个线程对同一个全局变量各加2000万，统计加锁解锁的消耗。
// 使用gettimeofday可以获取高精度当前时间。

#define NUM 10000000
typedef struct shareRes_s {
    long num;
    pthread_mutex_t mutex;
}shareRes_t, *pshareRes_t;

void* threadFun(void* arg) {
    pshareRes_t pshared = (pshareRes_t)arg;
    for(int i = 0; i < NUM; i++){
        pthread_mutex_lock(&pshared->mutex);
        pshared->num++;
        pthread_mutex_unlock(&pshared->mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    // 初始化锁和互斥资源
    shareRes_t shared;
    shared.num = 0;
    pthread_mutex_init(&shared.mutex, NULL);

    // 创建子线程
    pthread_t tid;
    int ret_create = pthread_create(&tid, NULL, threadFun, &shared);
    THREAD_ERROR_CHECK(ret_create, "pthread_create");
    
    // 执行加法，并获取两线程运行时间
    struct timeval tv_start, tv_end;
    gettimeofday(&tv_start, NULL);
    for(int i = 0; i < NUM; i++) {
        pthread_mutex_lock(&shared.mutex);
        shared.num++;
        pthread_mutex_unlock(&shared.mutex);
    }
    int ret_join = pthread_join(tid, NULL);
    THREAD_ERROR_CHECK(ret_join, "pthread_join");
    gettimeofday(&tv_end, NULL);
    
    // 总时间做除法，得到大概的lock时间
    long time_total = 
        (long)(tv_end.tv_sec - tv_start.tv_sec)*1000000000 + 
        (long)(tv_end.tv_usec - tv_start.tv_usec)*1000;
    double cost = (double)time_total / 40000000;

    printf("Lock/unlock cost time = %lf ns\n", cost);
    printf("num = %ld\n", shared.num);

    // 销毁锁
    pthread_mutex_destroy(&shared.mutex);
    return 0;
}

