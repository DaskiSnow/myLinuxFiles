#ifndef __CONSUMER_HH__
#define __CONSUMER_HH__

#include "Thread.hh"
#include "TaskQueue.hh"

class Consumer
: public Thread
{
public:
    Consumer(int id, TaskQueue<int> & tq);
private:
    void run() override;
private:
    int _id;
    TaskQueue<int> & _tq;
};

#endif
