#include "include/ThreadPool.hh"
#include <func.hh>

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskQue(queSize)
, _isExit(false)
{
    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool()
{}

void ThreadPool::start()
{
    // 创建并启动子线程
    for(size_t i = 0; i < _threadNum; ++i)
    {
        Thread * temp = new Thread(*this, bind(&ThreadPool::doTask, this));
        temp->start();   // 创建底层线程, 并执行调用doTask
        _threads.push_back(unique_ptr<Thread>(temp));
    }
}

void ThreadPool::stop()
{
    // 每隔一秒看任务队列是否为空
    while(!_taskQue.isEmpty())
    {
        sleep(1);
    }

    // 置_isExit标志位, 并唤醒可能的S线程
    _isExit = true;
    printf("_isExit == true!\n");
    _taskQue.wakeup();

    // 执行依次对每个子线程执行join(阻塞)
    for(size_t i = 0; i < _threadNum; ++i)
    {
        _threads[i]->join();
    }
}                

void ThreadPool::addTask(TaskCallBack taskcb)
{
    _taskQue.push(taskcb);
}

void ThreadPool::doTask()
{
    // 子线程调用
    while(!_isExit)
    {
        // 取任务
        TaskCallBack taskcb = getTask();

        // 执行任务, 要对回调函数进行判空!(function重载了bool()运算符)
        if(taskcb != nullptr)
        {
            taskcb();     
        }
        else 
        {
            printf("taskcb = nullptr, time to exit!\n");
        }
    }
}

TaskCallBack ThreadPool::getTask()
{
    TaskCallBack temp = _taskQue.pop();
    return temp;
}
