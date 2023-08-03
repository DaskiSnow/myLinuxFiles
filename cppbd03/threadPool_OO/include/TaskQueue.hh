#ifndef __TASKQUEUE_HH__
#define __TASKQUEUE_HH__

#include <queue>
#include "Mutex.hh"
#include "Condition.hh"
template<typename T>
class TaskQueue
{
public:
    TaskQueue(size_t cap);
    void push(const T & value);
    void pop();
    T & front();
private:
    bool isEmpty();
    bool isFull();
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
