#include <func.h>

void* thread_fun(void* arg) {
    sleep(3);
    int *pval = (int*)arg;
    printf("*pval = %d\n", *pval);
    return NULL;
}


int main(void){
    int *pval = (int*)malloc(sizeof(int));
    *pval = 666;

    pthread_t tid;
    int ret_create = pthread_create(&tid, NULL, thread_fun, pval);
    THREAD_ERROR_CHECK(ret_create, "thread_create");
    free(pval);
    printf("Main. Free over.\n");

    pthread_join(tid, NULL);
    printf("Child over.\n");
    return 0;

}
