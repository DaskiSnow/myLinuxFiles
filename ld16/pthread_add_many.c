#include <func.h>
#define NUM 10000000
// 设置一个全局变量，尝试使用两个线程各自对全局变量自增1000万次，输出嘴鸥结果

long result = 0;

void* thread_fun(void* arg) {
    for(int i = 0; i < NUM; i++){
        result++;
    }
    pthread_exit((void*)1);
}

int main()
{
    pthread_t tid;
    int ret_creat = pthread_create(&tid, NULL, thread_fun, NULL);
    THREAD_ERROR_CHECK(ret_creat, "pthread_create");
    for(int i = 0; i < NUM; i++){
        result++;
    }

    void *retval;
    int ret_join = pthread_join(tid, &retval); // 等待子线程执行完毕
    THREAD_ERROR_CHECK(ret_join, "pthread_join");
    
    printf("result = %ld\n", result);
    
}
