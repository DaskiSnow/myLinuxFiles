#include <func.h>

int turn = 0; // 实现轮流
void* threadFun(void* arg) {
    pthread_mutex_t *pmutex = (pthread_mutex_t*)arg;
    while(1){
        if(turn == 1){
            pthread_mutex_lock(pmutex);
            printf("Before B!\n");
            sleep(3);
            printf("After B\n");
            pthread_mutex_unlock(pmutex);
            turn = 0;
        }
    }
}

int main(int argc, char* argv[])
{
    // 初始化互斥锁
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    // 创建子线程
    pthread_t tid;
    int ret_create = pthread_create(&tid, NULL, threadFun, &mutex);
    THREAD_ERROR_CHECK(ret_create, "pthread_create");

    while(1){
        if(turn == 0) {
            pthread_mutex_lock(&mutex);
            printf("Before A!\n");
            sleep(3);
            printf("After A\n");
            turn = 1;
            pthread_mutex_unlock(&mutex);
        }
    }
    return 0;
}

