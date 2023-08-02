#include "include/Condition.hh"

Condition::Condition(pthread_mutex_t *pmutex)
{
    if(pmutex == NULL)
    {
        fprintf(stderr, "pmutex == nullptr\n");
        exit(1);
    }
    _pmutex = pmutex;
    int ret = pthread_cond_init(&_cond, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_cond_init");
}

Condition::~Condition()
{
    int ret = pthread_cond_destroy(&_cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_destroy");
}

void Condition::wait()
{
    int ret = pthread_cond_wait(&_cond, _pmutex);
    THREAD_ERROR_CHECK(ret, "pthread_cond_wait");
}

void Condition::signal()
{
    int ret = pthread_cond_signal(&_cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_signal");
}

void Condition::broadcast()
{
    int ret = pthread_cond_broadcast(&_cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_broadcast");
}
