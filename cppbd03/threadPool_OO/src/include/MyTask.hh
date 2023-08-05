#ifndef __MYTASK_HH__
#define __MYTASK_HH__

#include "Task.hh"

class MyTask
: public Task
{
public:
    void process() override;
};

#endif
