#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// 实现一个类只能生成堆对象，不能生成栈对象的代码，
// 并能做到正常回收该堆对象
class Point {
public:
    Point(int x = 0, int y = 0)
    : _ix(x)
    , _iy(y)
    {}

    void destroy() {
        delete this;
    }

private:
    int _ix;
    int _iy;
    ~Point() {
        cout << "~Point" << endl;
    } 
};

int main(int argc, char* argv[])
{
    // Point p; // error
    Point* pp = new Point;
    pp->destroy();
    return 0;
}

