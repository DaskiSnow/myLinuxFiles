#include "include/Thread.hh"

Thread::Thread()
: _tid(0)
{}

Thread::~Thread()
{}

void Thread::start()
{
    int ret = pthread_create(&_tid, NULL, threadFun, this);
    THREAD_ERROR_CHECK(ret, "pthread_create");
}

void Thread::join()
{
    int ret = pthread_join(_tid, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");
}

void* Thread::threadFun(void *arg)
{
    static_cast<Thread *>(arg)->run();
    return NULL;
}
