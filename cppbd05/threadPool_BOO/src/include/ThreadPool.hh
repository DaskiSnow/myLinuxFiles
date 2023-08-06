#ifndef __THREADPOOL_HH__
#define __THREADPOOL_HH__

#include <func.hh>
#include "Thread.hh"
#include "TaskQueue.hh"

using namespace std;
using TaskCallBack = function<void()>;
class ThreadPool
{
friend class WorkThread;
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();                  // 暂时用不到
    void start();                   // 创建线程, 并启动线程(主线程)
    void stop();                    // 设置_isExit, 唤醒可能存在的S线程, 等待子线程结束(主线程)
    void addTask(TaskCallBack cb);  // 添加Task到任务队列中(主线程)
private:
    void doTask();          // getTask->执行Task的process(子线程)
    TaskCallBack getTask(); // 取任务(子线程->doTask调用) 
private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;    
    TaskQueue<TaskCallBack> _taskQue;
    bool _isExit;
};

#endif

