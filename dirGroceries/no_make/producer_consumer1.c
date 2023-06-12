#include <func.h>

// 轮询情况

bool is_data_ready = false; // 共享变量，表示数据是否已经准备好
pthread_mutex_t mutex; // 用于保护共享变量的互斥锁

void *producer(void *arg) {
    // 生产数据
    pthread_mutex_lock(&mutex);
    is_data_ready = true; // 设置数据已经准备好
    pthread_mutex_unlock(&mutex);
}

void *consumer(void *arg) {
    while (true) {
        pthread_mutex_lock(&mutex);
        if (is_data_ready) {
            // 消费数据
            is_data_ready = false;
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
    }
}
