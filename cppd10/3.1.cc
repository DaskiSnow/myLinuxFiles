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
    int getX() {
        return _ix;
    }

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

    // 返回第一个点对象的指针
    Point* operator->() {
        return &_pt1;
    }

    
public:
    int mem = 3;
private:
    Point  _pt1;
    Point  _pt2;
};

void test() {
    Line l1(1, 2, 3, 4);
    int temp = l1->getX();
    cout << temp << endl;
}
int main(int argc, char* argv[])
{
    test();
    return 0;
}

