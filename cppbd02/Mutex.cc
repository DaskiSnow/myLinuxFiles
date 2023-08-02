#include "include/Mutex.hh"
Mutex::Mutex()
{
    int ret = pthread_mutex_init(&_mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");
}

Mutex::~Mutex()
{
    int ret = pthread_mutex_destroy(&_mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy");
}

void Mutex::lock()
{
    int ret = pthread_mutex_lock(&_mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lock");
}

int Mutex::trylock()
{
    int ret = pthread_mutex_trylock(&_mutex);    
    return ret;
}

void Mutex::unlock()
{
    int ret = pthread_mutex_unlock(&_mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock");
}

pthread_mutex_t* Mutex::getMutex()
{
    return &_mutex;
}

