#ifndef __TASK_HH__
#define __TASK_HH__
#include <stdio.h>
class Task
{
public:
    virtual void process()
    {
        printf("执行了空任务\n");
    }
};

#endif
