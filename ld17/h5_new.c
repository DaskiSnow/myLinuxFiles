#include <func.h>

int turn = 0; // 实现轮流
void* threadFun(void* arg) {
    pthread_mutex_t *pmutex = (pthread_mutex_t*)arg;
    while(1){ // 轮询flag条件是否成立
        pthread_mutex_lock(pmutex);
        if(turn != 1) { // flag不成立
            pthread_mutex_unlock(pmutex);
            continue;
        } // flag成立
        break;
    }
    // 临界区
    printf("Before B!\n");
    sleep(3);
    printf("After B\n");
    turn = 0;
    pthread_mutex_unlock(pmutex);
    // 临界区end

    return NULL;
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

    while(1){ // 轮询
        pthread_mutex_lock(&mutex);
        if(turn != 0) { // 不满足flag
            pthread_mutex_unlock(&mutex);
            continue;
        } // 满足flag
        break;
    }
    // 临界区
    printf("Before A!\n");
    sleep(3);
    printf("After A\n");
    turn = 1;
    pthread_mutex_unlock(&mutex);
    // 临界区end
    
    pthread_join(tid, NULL);
    return 0;
}

