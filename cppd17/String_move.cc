#include <string.h>
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class String
{
public:
    String()
    : _pstr(new char[1]())
    {
        cout << "String()" << endl;
    }

    // 具有值语义的拷贝构造函数(左值实参)
    String(const String & rhs)
    {
        cout << "String(const String & rhs)" << endl;
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }

    String(const char * cstr)
    {
        cout << "String(const char * cstr)" << endl;
        if(!cstr) return;
        _pstr = new char[strlen(cstr) + 1]();
        strcpy(_pstr, cstr);
    }
    
    // 移动构造函数(右值实参)
    String(String && rhs)
    {
        cout << "String(String && rhs)" << endl;
        _pstr = rhs._pstr;
        rhs._pstr = nullptr;
    }

    // 具有值语义的赋值运算符函数(左值实参)
    String & operator=(const String & rhs)
    {
        cout << "String & operator=(const String & rhs)" << endl;
        if(this == &rhs) return *this;
        if(_pstr)
        {
            delete [] _pstr;
        }
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
        return *this;
    }

    // 移动赋值运算符函数(右值实参)
    String & operator=(String && rhs)
    {
        cout << "String & operator=(String && rhs)" << endl;
        // 判断自移动
        if(this == &rhs) return *this;
        // 释放左操作数
        if(_pstr) delete [] _pstr;
        // 浅拷贝
        _pstr = rhs._pstr;
        rhs._pstr = nullptr;

        return *this;
    }


    ~String()
    {
        cout << " ~String()" << endl;
        if(_pstr)
        {
            delete [] _pstr;
        }
    }
private:
    char * _pstr;
};

void test()
{
    cout << "----------Move Constructor-----------" << endl;
    String s1 = "Snow";
    cout << "----------Move Operator= ------------" << endl;
    s1 = "Yuki";
    cout << "----------Move Constructor-----------" << endl;
    String s2 = String(s1);
    cout << "-------------------------------------" << endl;
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}
