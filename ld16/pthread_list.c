#include <func.h>
// 在主线程中创建一个链表，并插入若干个结点，
// 将其传递给子线程，在子线程当中遍历所有的链表结点。

typedef struct node_s {
    int val;
    struct node_s* next;
}node_t;

void* thread_fun(void* arg) {
    // 子线程遍历所有链表结点
    node_t *head = (node_t*)arg;
    node_t* p = head;
    while(p){
        printf("%d ", p->val);
        p=p->next;
    }
    printf("\n");

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    // 创建链表并插入5个结点
    node_t node_5 = {5, NULL};
    node_t node_4 = {4, &node_5};
    node_t node_3 = {3, &node_4};
    node_t node_2 = {2, &node_3};
    node_t node_1 = {1, &node_2};

    // 创建子线程
    pthread_t tid;
    pthread_create(&tid, NULL, thread_fun, &node_1);

    // 等待子线程结束
    pthread_join(tid, NULL);
    return 0;
}

