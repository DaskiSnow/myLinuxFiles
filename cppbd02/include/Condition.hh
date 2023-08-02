#ifndef __CONDITION_HH__
#define __CONDITION_HH__

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

class Condition
{
public:
    Condition(pthread_mutex_t *pmutex);
    ~Condition();
    void wait();
    void signal();
    void broadcast();
private:
    pthread_mutex_t *_pmutex;
    pthread_cond_t _cond;
};

#endif
