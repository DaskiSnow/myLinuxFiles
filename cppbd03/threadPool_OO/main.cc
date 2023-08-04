#include <func.hh>
#include "include/ThreadPool.hh"
#include "include/MyTask.hh"
#include "include/TaskQueue.hh"
using namespace std;

int main(int argc, char* argv[])
{
    ThreadPool pool(3, 10);
    pool.start();
    pool.stop();
    return 0;
}

