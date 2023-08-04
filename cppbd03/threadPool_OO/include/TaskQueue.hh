#ifndef __TASKQUEUE_HH__
#define __TASKQUEUE_HH__

#include <queue>
#include "Mutex.hh"
#include "Condition.hh"
template<typename T>
class TaskQueue
{
friend class ThreadPool;
public:
    TaskQueue(size_t cap);
    void push(const T & value);
    void pop();
    T & front();
private:
    bool isEmpty();
    bool isFull();
    void wakeup();  // 结束时唤醒子线程, 主线程结束时设置_isExit后调用, 防止子线程仍处于等待任务状态而无法退出
private:
    std::size_t _capacity;
    std::size_t _size;
    Mutex _mutex;    
    Condition _notEmpty;
    Condition _notFull;
    std::queue<T> _q;
};
#include "TaskQueue.tcc"
#endif
