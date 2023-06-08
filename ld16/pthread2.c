#include <func.h>


//多线程共享堆空间
void * threadFunc(void *arg){
    char *pHeap = (char *)arg;
    printf("I am child thread, tid = %lu\n",
           pthread_self());
    strcpy(pHeap,"world");
    printf("child thread, %s\n",pHeap);
    return NULL;
} 

int main()
{
    pthread_t tid;
    char *pHeap = (char *)malloc(20);
    strcpy(pHeap,"hello");
    int ret = pthread_create(&tid,NULL,threadFunc,(void *)pHeap);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread, tid = %lu\n",
           pthread_self());
    sleep(1);
    printf("parent thread, %s\n",pHeap);
    free(pHeap);
    return 0;
}
