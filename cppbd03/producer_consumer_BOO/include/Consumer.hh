#ifndef __CONSUMER_HH__
#define __CONSUMER_HH__

#include "Thread.hh"
#include "TaskQueue.hh"

class Consumer
{
public:
    Consumer(int id, TaskQueue<int> & tq);
public:
    void run();
private:
    int _id;
    TaskQueue<int> & _tq;
};

#endif
