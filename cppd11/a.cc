#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;

class Base {

};

// 至少有一个类类型和枚举类型，但C++Primer中说到，应该是自定义类型和枚举类型
ostream & operator<<(ostream & os, char ch) 
{
    cout << "ostream & operator<<(ostream & os, char ch) " << endl;
    os << "abc";
    return os;
}

int main(int argc, char* argv[])
{
    char ch = 'a';
    Base base;
    cout << ch << endl;
    return 0;
}




