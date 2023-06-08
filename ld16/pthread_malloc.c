#include <func.h>
// 构造一个堆空间崩溃的例子

void handler(int signum) {
    printf("signum = %d\n", signum);
}

void* thread_fun(void* arg) {
    signal(SIGSEGV, handler);

    // 子线程可能free后访问
    int *pnum = (int*)arg;
    printf("Child. pnum = %d\n", *pnum);
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{   
    int* pnum = (int*)malloc(sizeof(int));
    *pnum = 250;

    pthread_t tid;
    int ret_create = pthread_create(&tid, NULL, thread_fun, pnum);
    THREAD_ERROR_CHECK(ret_create, "pthread_create");

    free(pnum);

    return 0;
}

