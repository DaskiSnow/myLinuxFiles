#include "include/ThreadPool.hh"
#include "include/WorkThread.hh"
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
        WorkThread * temp = new WorkThread(*this);
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

void ThreadPool::addTask(Task *ptask)
{
    _taskQue.push(ptask);
}

void ThreadPool::doTask()
{
    // 子线程调用
    while(!_isExit)
    {
        // 取任务
        Task * ptask = getTask();

        // 执行任务(2nd引用多态)
        if(ptask)
        {
            ptask->process();     
        }
        else
        {
            // 返回了空指针, 说明线程检测到结束标志
            printf("isExit = true! A WorkThread Exit!\n");
        }
    }
}

Task * ThreadPool::getTask()
{
    Task * temp = _taskQue.pop();
    return temp;
}
