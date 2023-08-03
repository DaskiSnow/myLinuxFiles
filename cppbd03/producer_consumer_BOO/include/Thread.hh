#ifndef __THREAD_HH__
#define __THREAD_HH__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <functional>
using namespace std;
#define THREAD_ERROR_CHECK(retval, msg) \
{                                       \
    if(retval != 0)                     \
    {                                   \
        fprintf(stderr, "%s: %s\n", msg, strerror(retval)); \
        exit(1);                        \
    }                                   \
}

class Thread
{
public:
    Thread(function<void()> run);
    virtual ~Thread();
    void start();
    void join();

private:
    static void* threadFun(void *arg);

private:
    pthread_t _tid;
    function<void()> _run;
};

#endif
