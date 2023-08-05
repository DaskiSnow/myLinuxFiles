#include <func.hh>
#include "include/ThreadPool.hh"
#include "include/MyTask.hh"
#include "include/TaskQueue.hh"
using namespace std;

class DueTask
: public Task
{
    void process()
    {
        /* printf("你怎么回事小老弟\n"); */
    }
};

void test2()
{
    MyTask mytask;
    static DueTask duetask;
    ThreadPool pool(6, 1000);
    pool.start();
    int cnt = 10000000;
    while(cnt--)
    {
        pool.addTask(&mytask);
    }
    pool.addTask(&duetask);
    printf("添加任务完成\n");
    pool.stop();
}

void test()
{
    MyTask * pmytask = new MyTask;
    pmytask->process();
}

int main(int argc, char* argv[])
{
    test2();
    return 0;
}

