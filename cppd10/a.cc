#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

// 降序排列
bool myGreater(int a, int b) {
    return a > b;
}

int main(int argc, char* argv[])
{
    bool (*cmp)(int, int);
    cmp = myGreater;
    cout << cmp(2, 1) << endl;
    return 0;
}

