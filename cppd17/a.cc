#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class String
{
public:
    String(int num)
    : _num(num)
    {}

    ~String()
    {
        cout << "~String() " << _num <<endl;
    }
public:
    int _num;
};

int main(int argc, char* argv[])
{
    return 0;
}

