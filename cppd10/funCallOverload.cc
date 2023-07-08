#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class absInt {
public:
    absInt(int value)
    : _value(value)
    {}

    // 函数调用运算符重载
    int operator()(int value) {
        return value < 0 ? -value : value;
    }

private:
    int _value;

};

int main(int argc, char* argv[])
{
    int absint = absInt(5)(-3);
    cout << absint << endl;
    return 0;
}

