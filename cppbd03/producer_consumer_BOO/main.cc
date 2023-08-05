#include <iostream>
#include <string>
#include "include/TaskQueue.hh"
#include "include/Producer.hh"
#include "include/Consumer.hh"

using namespace std;

void test()
{
    TaskQueue<int> tq(1);
    Producer p1(1, tq);
    Consumer c2(2, tq);
    Consumer c3(3, tq);
    Thread producer_thread(bind(&Producer::run, &p1));
    Thread consumerA_thread(bind(&Consumer::run, &c2));
    Thread consumerB_thread(bind(&Consumer::run, &c3));
    producer_thread.start();
    producer_thread.start();
    consumerA_thread.start();
    /* consumerB_thread.start(); */
    producer_thread.join();
    consumerA_thread.join();
    consumerB_thread.join();
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

