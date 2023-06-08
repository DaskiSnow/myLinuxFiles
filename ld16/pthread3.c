#include <func.h>

//各个子线程会打印相同的结果
void * threadFunc(void *arg){
    printf("I am child thread, tid = %lu\n",
           pthread_self());
    int * pval = (int *)arg;
    printf("child, val = %d\n",*pval);
    return NULL;
} 

int main()
{
    pthread_t tid;
    int val = 1001;
    int ret = pthread_create(&tid,NULL,threadFunc,(void *)&val);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    val = 1002;
    ret = pthread_create(&tid,NULL,threadFunc,(void *)&val);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread, tid = %lu\n",
           pthread_self());
    sleep(1);
    return 0;
}
