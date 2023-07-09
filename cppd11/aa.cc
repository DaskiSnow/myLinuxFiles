#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

// 重载运算符+

class MyInteger {
public:
    MyInteger(int value = 0)
    : _value(value)
    {}

    int operator()(const MyInteger & rhs = MyInteger(100)) 
    {
        return _value + rhs._value;    
    }

    int operator+(const MyInteger & rhs) 
    {
        return _value + rhs._value;
    }

private:
    int _value;
};

int main(int argc, char* argv[])
{
    MyInteger num1(10);
    MyInteger num2(20);
    cout << num1+num2 << endl;
    return 0;
}

