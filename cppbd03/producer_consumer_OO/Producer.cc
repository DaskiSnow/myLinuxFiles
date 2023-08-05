#include "include/Producer.hh"
#include <unistd.h>

Producer::Producer(int id, TaskQueue<int> & tq)
: _id(id)
, _tq(tq)
{}

void Producer::run()
{
    while(1)
    {
        _tq.push(_id);
        printf("produce\n");
        sleep(2);
    }
}
