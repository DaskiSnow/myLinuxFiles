// 队列头文件
typedef struct node_q {
    int no;
    struct node_q *next;
}Node;

typedef struct {
    Node *front;
    Node *rear;
}LiQueue;

void queue_create(LiQueue** ppqueue);
void queue_destroy(LiQueue* pqueue);
void queue_push(LiQueue* pqueue, int no);
void queue_pop(LiQueue* pqueue, int *pno);
void queue_peek(LiQueue* pqueue, int *pno);
bool queue_empty(LiQueue* pqueue);

