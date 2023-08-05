#ifndef __CONDITION_HH__
#define __CONDITION_HH__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mutex.hh"

#define THREAD_ERROR_CHECK(retval, msg) \
{                                       \
    if(retval != 0)                     \
    {                                   \
        fprintf(stderr, "%s: %s\n", msg, strerror(retval)); \
        exit(1);                        \
    }                                   \
}

class Condition
{
public:
    Condition(Mutex *pmutex);
    ~Condition();
    void wait();
    void signal();
    void broadcast();
private:
    Mutex *_pmutex;
    pthread_cond_t _cond;
};

#endif
