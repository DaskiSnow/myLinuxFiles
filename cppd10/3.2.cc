#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Date {
public:
    int getValue() {
        return _value;
    }
private:
    int _value = 100;
};

class FirstL {
public:
    FirstL()
    : _data(new Date)
    {}

    ~FirstL() {
        if(_data) {
            delete _data;
            _data = nullptr;
        }
    }

    // 重载箭头运算符, 返回类型为指针
    Date * operator->() {
        return _data;
    }

private:
    Date * _data;
};

class SecL {
public:
    SecL()
    : _firstL(new FirstL)
    {}
    
    ~SecL() {
        if(_firstL) {
            delete _firstL;
            _firstL = nullptr;
        }
    }

    // 重载箭头运算符，返回类型应为对象引用
    FirstL & operator->() {
        return *_firstL;
    }

private:
    FirstL * _firstL;
};

int main(int argc, char* argv[])
{
    SecL secl;
    cout << secl->getValue() << endl;
    return 0;
}

