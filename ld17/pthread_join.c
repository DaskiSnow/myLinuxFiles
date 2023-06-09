#include <func.h>
// 书写程序，创建3个子线程，然后等待所有的子线程终止，最后获取其退出状态。

void* threadFun1(void* arg) {
    long num = (long)arg;
    num++;
    sleep(1);
    pthread_exit((void*)num);
} 

void* threadFun2(void* arg) {
    long num = (long)arg;
    num++;
    sleep(2);
    pthread_exit((void*)num);
} 

void* threadFun3(void* arg) {
    long num = (long)arg;
    num++;
    sleep(3);
    pthread_exit((void*)num);
} 

int main(int argc, char* argv[])
{
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, threadFun1, (void*)1);
    pthread_create(&tid2, NULL, threadFun2, (void*)2);
    pthread_create(&tid3, NULL, threadFun3, (void*)3);

    void *ret1, *ret2, *ret3;
    pthread_join(tid1, &ret1);
    printf("ret1 = %ld\n", (long)ret1);
    pthread_join(tid2, &ret2);
    printf("ret2 = %ld\n", (long)ret2);
    pthread_join(tid3, &ret3);
    printf("ret3 = %ld\n", (long)ret3);

    return 0;

}

