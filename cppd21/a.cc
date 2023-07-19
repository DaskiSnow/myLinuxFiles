#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

void func()
{
    cout << "void func()" << endl;
}

int main(int argc, char **argv)
{
    cout << "begin main...." << endl;
    atexit(func);
    atexit(func);
    atexit(func);
    atexit(func);
    cout << "finish main..." << endl;
    return 0;
}


