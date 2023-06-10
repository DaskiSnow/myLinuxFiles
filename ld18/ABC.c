#include <func.h>
// 现在有两个线程t1和t2，t1 打印 A 和 C，t2 打印 B。
// 书写代码，使用条件变量每次的显示顺序都是A->B->C。

typedef struct shareRes_s {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int turn; // 0 1 2
}shareRes_t;

void* threadFun1(void* arg) {
    shareRes_t *pshared = (shareRes_t *)arg;

    // 打印 A
    pthread_mutex_lock(&pshared->mutex);
    if(pshared->turn != 0) {
        pthread_cond_wait(&pshared->cond, &pshared->mutex);
    }
    printf("A ");
    pshared->turn = 1;
    pthread_cond_signal(&pshared->cond);
    pthread_mutex_unlock(&pshared->mutex);

    // 打印 C
    pthread_mutex_lock(&pshared->mutex);
    if(pshared->turn != 2) {
        pthread_cond_wait(&pshared->cond, &pshared->mutex);
    }
    printf("C\n");
    pthread_mutex_unlock(&pshared->mutex);

    return NULL;
}

void* threadFun2(void* arg) {
    shareRes_t *pshared = (shareRes_t *)arg;

    // 打印 B
    pthread_mutex_lock(&pshared->mutex);
    if(pshared->turn != 1) {
        pthread_cond_wait(&pshared->cond, &pshared->mutex);
    }
    printf("B ");
    pshared->turn = 2;
    pthread_cond_signal(&pshared->cond);
    pthread_mutex_unlock(&pshared->mutex);

    return NULL;
}

int main(int argc, char* argv[])
{
    // 创建锁，初始化锁和条件变量
    shareRes_t shared;
    int ret = pthread_cond_init(&shared.cond, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_cond_init");
    ret = pthread_mutex_init(&shared.mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");
    shared.turn = 0;

    // 创建子线程
    pthread_t tid1, tid2;
    ret = pthread_create(&tid1, NULL, threadFun1, &shared);
    THREAD_ERROR_CHECK(ret, "thread_create 1");
    ret = pthread_create(&tid2, NULL, threadFun2, &shared);
    THREAD_ERROR_CHECK(ret, "thread_create 2");

    // 等待子线程结束
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // 销毁锁和条件变量
    pthread_mutex_destroy(&shared.mutex);
    pthread_cond_destroy(&shared.cond);

    return 0;
}

