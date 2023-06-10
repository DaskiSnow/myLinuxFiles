#include <func.h>
// 在AB事件之外不使用sleep，使用条件变量，确保B一定在A完成之后运行。

typedef struct shareRes_s {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int turn; // 0 1
}shareRes_t;

void* threadFun(void* arg) {
    shareRes_t *pshared = (shareRes_t *)arg;

    // 子线程同步地执行事件B
    pthread_mutex_lock(&pshared->mutex);
    while(pshared->turn != 1) {
        pthread_cond_wait(&pshared->cond, &pshared->mutex);
    }
    printf("Before B!\n");
    sleep(3);
    printf("After B!\n");
    pthread_mutex_unlock(&pshared->mutex);

    return NULL;
}

int main(int argc, char* argv[])
{
    // 定义结构体，初始化互斥资源turn、锁mutex 和 条件变量cond
    shareRes_t shared;
    shared.turn = 0;
    int ret = pthread_mutex_init(&shared.mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");
    ret = pthread_cond_init(&shared.cond, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_cond_init");

    // 创建子线程
    pthread_t tid;
    ret = pthread_create(&tid, NULL, threadFun, &shared);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    // 主线程同步地执行事件A
    pthread_mutex_lock(&shared.mutex);
    while(shared.turn != 0) {
        pthread_cond_wait(&shared.cond, &shared.mutex);
    }
    printf("Before A!\n");
    sleep(3);
    printf("After A!\n");
    shared.turn = 1;                   //易忘：设置turn
    pthread_cond_signal(&shared.cond); //易忘：发信号
    pthread_mutex_unlock(&shared.mutex);

    // 等待子线程终结
    pthread_join(tid, NULL);

    return 0;
}

