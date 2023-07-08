#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;


class Base {
public:
    Base(int num)
    : _num(num)
    {}

    // 重载相加运算符
    friend int operator+(Base, Base);

private:
    int _num;
};

// 反常识重载
int operator+(Base a, Base b) {
    return b._num - a._num;
}

int main(int argc, char* argv[])
{
    // 编写Base类使下列代码输出为1

    int i=2;
    int j=7;

    Base x(i);
    Base y(j);
    cout << (x+y == j - i) << endl;
    // 提示：本题考查的其实就是运算符重载的知识点。
    return 0;
}

