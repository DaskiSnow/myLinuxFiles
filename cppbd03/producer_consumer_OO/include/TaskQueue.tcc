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
, _isExit(false)
{}

template<typename T>
void TaskQueue<T>::push(const T & value)
{
    _mutex.lock();
    while(isFull() && !_isExit)
    {
        _notFull.wait();
    }
    if(_isExit)
    {
        _mutex.unlock();
        return;
    }
    // 临界区：生产货物
    _q.push(value);
    ++_size;
    _notEmpty.broadcast();
    _mutex.unlock();
}

// PS: !!此处不能为引用, 否则将返回了一个局部变量的引用!!
template<typename T>
T TaskQueue<T>::pop()
{
    _mutex.lock();
    while(isEmpty() && !_isExit)
    {
        _notEmpty.wait();
    }
    if(_isExit)
    {
        _mutex.unlock();
        static T nondata;
        return nondata;
    }
    // 临界区：消费货物
    T temp = _q.front();
    _q.pop();
    --_size;
    _notFull.broadcast();
    if(temp == NULL) printf("NULL\n");
    _mutex.unlock();
    return temp;
}

template<typename T>
T TaskQueue<T>::front()
{
    _mutex.lock();
    while(isEmpty() && !_isExit)
    {
        _notEmpty.wait();
    }
    if(_isExit)
    {
        _mutex.unlock();
        static T nondata;
        return nondata;
    }
    _mutex.unlock();
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
void TaskQueue<T>::wakeup()
{
    _isExit = true;
    _notEmpty.broadcast();
    _notFull.broadcast();
}

#endif
