#ifndef __MUTEX_HH__
#define __MUTEX_HH__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THREAD_ERROR_CHECK(retval, msg) \
{                                       \
    if(retval != 0)                     \
    {                                   \
        fprintf(stderr, "%s: %s\n", msg, strerror(retval)); \
        exit(1);                        \
    }                                   \
}           

class Mutex
{
public:
    Mutex();
    ~Mutex();
    void lock();
    int trylock();
    void unlock();
    pthread_mutex_t* getMutex();
private:
    pthread_mutex_t _mutex;
};

#endif
