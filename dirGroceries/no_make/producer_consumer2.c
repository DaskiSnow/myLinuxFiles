#include <func.h>

// 引入条件变量后，避免了为了查看条件是否成立而不断轮询的情况

bool is_data_ready = false; // 共享变量，表示数据是否已经准备好
pthread_mutex_t mutex; // 用于保护共享变量的互斥锁
pthread_cond_t cond; // 条件变量

void *producer(void *arg) {
    // 生产数据
    pthread_mutex_lock(&mutex);
    is_data_ready = true; // 设置数据已经准备好
    pthread_cond_signal(&cond); // 通知消费者线程数据已经准备好
    pthread_mutex_unlock(&mutex);
}

void *consumer(void *arg) {
    pthread_mutex_lock(&mutex);
    while (!is_data_ready) { // 等待数据准备好
        pthread_cond_wait(&cond, &mutex); // 等待条件变量，同时释放互斥锁
    }
    // 消费数据
    is_data_ready = false;
    pthread_mutex_unlock(&mutex);
}
