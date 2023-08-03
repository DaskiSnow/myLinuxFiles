#ifndef __TASKQUEUE_TCC__
#define __TASKQUEUE_TCC__

#include "TaskQueue.hh"

template<typename T>
TaskQueue<T>::TaskQueue(size_t cap)
: _capacity(cap)
, _size(0)
, _mutex(Mutex())
, _notEmpty(Condition(&_mutex))
, _notFull(Condition(&_mutex))
{}

template<typename T>
void TaskQueue<T>::push(const T & value)
{
    _mutex.lock();
    while(isFull())
    {
        _notFull.wait();
    }
    // 临界区：生产货物
    _q.push(value);
    ++_size;
    /* printf("produce: _size = %ld, _capacity = %ld\n", _size, _capacity); */
    _notEmpty.broadcast();
    _mutex.unlock();
}

template<typename T>
void TaskQueue<T>::pop()
{
    _mutex.lock();
    while(isEmpty())
    {
        _notEmpty.wait();
    }
    // 临界区：消费货物
    _q.pop();
    --_size;
    /* printf("consume: _size = %ld, _capacity = %ld\n", _size, _capacity);; */
    _notFull.broadcast();
    _mutex.unlock();
}

template<typename T>
T & TaskQueue<T>::front()
{
    if(isEmpty())
    {
        // 不可能进入到这里面
        static T nondate;
        return nondate;
    }
    return _q.front();
}

template<typename T>
bool TaskQueue<T>::isEmpty()
{
    return _size == 0;
}

template<typename T>
bool TaskQueue<T>::isFull()
{
    return _size == _capacity;
}

template<typename T>
void wakeup()
{
    _notEmpty.broadcast();
    _notFull.broadcast();
}

#endif
