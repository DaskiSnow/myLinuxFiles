#include <func.hh>
#include "include/ThreadPool.hh"
#include "include/MyTask.hh"
#include "include/TaskQueue.hh"
using namespace std;

int main(int argc, char* argv[])
{
    MyTask mytask;
    ThreadPool pool(3, 10);
    pool.start();
    int cnt = 15;
    while(cnt--)
    {
        pool.addTask(&mytask);
    }
    pool.stop();
    return 0;
}

