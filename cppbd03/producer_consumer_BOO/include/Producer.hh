#ifndef __PRODUCER_HH__
#define __PRODUCER_HH__

#include "Thread.hh"
#include "TaskQueue.hh"

class Producer
{
public:
    Producer(int id, TaskQueue<int> & tq);
public:
    void run();
private:
    int _id;
    TaskQueue<int> & _tq;
};

#endif
