#ifndef __WORKTHREAD_HH__
#define __WORKTHREAD_HH__

#include "Thread.hh"
#include "ThreadPool.hh"

class WorkThread
: public Thread
{
public:
    WorkThread(ThreadPool & pool);
    void run() override;
private:
    ThreadPool & _pool;
};

#endif
