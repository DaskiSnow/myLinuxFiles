#include "include/TaskQueue.hh"
#include <iostream>
using namespace std;

template<typename T>
TaskQueue<T>::TaskQueue(size_t cap)
: _capacity(cap)
, _size(0)
, _mutex(Mutex())
, _cond(Condition(&_mutex))
{}

template<typename T>
void TaskQueue<T>::push(const T & value)
{
    _mutex.lock();
    while(isFull())
    {
        _cond.wait();
    }
    // 临界区：生产货物
    _q.push(value);
    ++_size;
    printf("produce: _size = %u, _capacity = %u\n", _size, _capacity);
    _cond.broadcast();
    _mutex.unlock();
}

template<typename T>
void TaskQueue<T>::pop()
{
    _mutex.lock();
    while(isEmpty())
    {
        _cond.wait();
    }
    // 临界区：消费货物
    T res = _q.front();
    _q.pop();
    --_size;
    printf("consume: _size = %u, _capacity = %u\n", _size, _capacity);;
    _cond.broadcast();
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

