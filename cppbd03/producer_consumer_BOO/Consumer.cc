#include "include/Consumer.hh"
#include <unistd.h>

Consumer::Consumer(int id, TaskQueue<int> & tq)
: _id(id)
, _tq(tq)
{}

void Consumer::run() 
{
    while(1)
    {
        _tq.pop();
        printf("consume\n");
        sleep(2);
    }
}
