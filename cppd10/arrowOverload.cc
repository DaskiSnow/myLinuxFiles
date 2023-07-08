#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Point {
public:
    friend class Line;

    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {}

    // 复合赋值运算符重载（成员函数）
    Point & operator+=(Point & rhs) {
        ++rhs._ix;        
        ++rhs._iy;        
        return rhs;
    }
    
    // 箭头运算符重载
    // 总结：返回对象的指针/返回一个重载了箭头运算符的对象
    Point * operator->() {
        return this;
    } 

    int getx() const {
        return _ix;
    }

public:
    int mem = 12;
private:
    int _ix;
    int _iy;
};

class Line {
public:
    
private:
    Point pt1;
    Point pt2;
};

int main(int argc, char* argv[])
{
    Point p(3,4); 
    cout << p->getx() << endl;
    return 0;
}

