#include "include/WorkThread.hh"

WorkThread::WorkThread(ThreadPool & pool)
: _pool(pool)
{}

void WorkThread::run()
{
    // 调用_pool的doTask
    _pool.doTask();
}
