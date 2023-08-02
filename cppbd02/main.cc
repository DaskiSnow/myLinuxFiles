#include <iostream>
#include <string>
#include "include/Consumer.hh"
#include "include/Producer.hh"
#include "include/TaskQueue.hh"

using namespace std;

void test()
{
    TaskQueue<int> tq(5);
    Producer p1(1, tq);
    Consumer c2(2, tq);
    Consumer c3(3, tq);
    p1.start();
    c2.start();
    p1.join();
    c2.join();
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

