#include <func.h>
#include "LiQueue.h"

// 多生产者、多消费者问题(条件变量、broadcast)

typedef struct shareRes_s {
    unsigned int seed; // 随机种子
    int storage; // 商品库存
    LiQueue* pqueue; // 商品队列
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareRes_t;

void* threadConsumer(void* arg) {
    sleep(5);
    shareRes_t *pshareRes = (shareRes_t *)arg;
    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        while(pshareRes->storage <= 0) { // 货物告罄, 并通知Producer
            pthread_cond_wait(&pshareRes->cond, &pshareRes->mutex);
        }
        // 临界区
        // 消费货物
        int no; // 商品no
        pshareRes->storage--;
        queue_pop(pshareRes->pqueue, &no);
        printf("Consume product, no = %d; storage = %d\n", no, pshareRes->storage);
        pthread_cond_broadcast(&pshareRes->cond);
        pthread_mutex_unlock(&pshareRes->mutex);
        // 临界区end
        sleep(1);
    }

    return NULL;
}

void* threadProducer(void* arg) {
    shareRes_t *pshareRes = (shareRes_t *)arg;

    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        while(pshareRes->storage >= 10) { // 商品数目达到最大值
            pthread_cond_wait(&pshareRes->cond, &pshareRes->mutex);
        }
        // 临界区
        // 生产货物，并通知Consumer
        pshareRes->storage++;
        int no = rand_r(&pshareRes->seed);
        queue_push(pshareRes->pqueue, no);
        printf("Produce product, no = %d; storage = %d\n", no, pshareRes->storage);
        pthread_cond_broadcast(&pshareRes->cond);
        pthread_mutex_unlock(&pshareRes->mutex);
        // 临界区end
        sleep(3);
    }

    return NULL;
}

int main(int argc, char* argv[])              // ERROR_CHECK X
{   
    unsigned int seed = time(NULL); // 设置随机种子
    // 初始化商品队列, 8个商品
    LiQueue* pqueue;
    queue_create(&pqueue);
    for(int i = 0; i < 8; i++) {
        queue_push(pqueue, rand_r(&seed));
    }

    // 定义锁、初始化锁、条件变量、互斥资源
    shareRes_t shareRes;
    shareRes.seed = seed;
    shareRes.storage = 8;
    shareRes.pqueue = pqueue;
    pthread_mutex_init(&shareRes.mutex, NULL);
    pthread_cond_init(&shareRes.cond, NULL);

    // 创建子线程: 3个生产者，2个消费者
    pthread_t p1, p2, p3, c1, c2; 
    int ret = pthread_create(&p1, NULL, threadProducer, &shareRes);
    THREAD_ERROR_CHECK(ret, "pthread create p1");
    ret = pthread_create(&p2, NULL, threadProducer, &shareRes);
    THREAD_ERROR_CHECK(ret, "pthread create p2");
    ret = pthread_create(&p3, NULL, threadProducer, &shareRes);
    THREAD_ERROR_CHECK(ret, "pthread create p3");
    ret = pthread_create(&c1, NULL, threadConsumer, &shareRes);
    THREAD_ERROR_CHECK(ret, "pthread create c1");
    ret = pthread_create(&c2, NULL, threadConsumer, &shareRes);
    THREAD_ERROR_CHECK(ret, "pthread create c2");

    // 等待子线程
    ret = pthread_join(p1, NULL);
    THREAD_ERROR_CHECK(ret, "pthread join p1");
    ret = pthread_join(p2, NULL);
    THREAD_ERROR_CHECK(ret, "pthread join p2");
    ret = pthread_join(p3, NULL);
    THREAD_ERROR_CHECK(ret, "pthread join p3");
    ret = pthread_join(c1, NULL);
    THREAD_ERROR_CHECK(ret, "pthread join c1");
    ret = pthread_join(c2, NULL);
    THREAD_ERROR_CHECK(ret, "pthread join c2");

    // 摧毁锁、条件变量、释放队列
    pthread_mutex_destroy(&shareRes.mutex); 
    pthread_cond_destroy(&shareRes.cond); 
    queue_destroy(shareRes.pqueue);

    return 0;
}

