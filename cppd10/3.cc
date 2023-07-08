#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;

class Point {
public:
    Point(int ix, int iy)
    : _ix(ix)
    , _iy(iy)
    {}

    friend class Line;
    friend ostream & operator<<(ostream & os, const Point & pt);

private:
    int _ix;
    int _iy;
};

class Line {
public:
    Line(int x1, int y1, int x2, int y2)
    : _pt1(x1, y1)
    , _pt2(x2, y2)
    {}

    void print()
    {
        cout << _pt1 << "-->" << _pt2 << endl;
    }

    Line * operator->() {
        return this;
    }

    
public:
    int mem = 3;
private:
    Point  _pt1;
    Point  _pt2;
};

// 重载输出流运算符
ostream & operator<<(ostream & os, const Point & pt) {
    os << "(" <<pt._ix << ", " << pt._iy << ")";
    return os;
}

// C++ 成员指针访问运算符的例子
void test() {
    Line(1, 2, 3, 4).print();
}
int main(int argc, char* argv[])
{
    return 0;
}

