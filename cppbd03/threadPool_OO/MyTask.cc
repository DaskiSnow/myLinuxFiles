#include "include/MyTask.hh"
#include <func.hh>

void MyTask::process()
{
    // 生产一次随机数
    srand(time(NULL));    
    int num = rand() % 100;
    printf("生产了一次随机数: %d\n", num);
}
