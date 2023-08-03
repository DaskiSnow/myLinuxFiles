#include "include/Thread.hh"

Thread::Thread(function<void()> run)
: _tid(0)
, _run(std::move(run))
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
    Thread * pthread = static_cast<Thread *>(arg);
    pthread->_run();   
    return NULL;
}
