#include <func.h>

//多线程共享数据段
int global= 100;

void * threadFunc(void *arg){
    printf("I am child thread, tid = %lu\n",pthread_self());
    printf("child thread, global = %d\n", global);
    return NULL;
} 

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread, tid = %lu\n",
           pthread_self());
    // sleep(5);
    global = 200;
    printf("main thread, global = %d\n", global);
    sleep(1);
    return 0;
}
