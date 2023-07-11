#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Base
{
public:
    Base(int value)
    : _value(value)
    {}

    operator int()
    {
        return _value;
    }
private:
    int _value;
};


int main(int argc, char* argv[])
{
    cout << Base(3).operator int() << endl;
    return 0;
}

