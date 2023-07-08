#include "6_Line.hh"
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

// 6_Line.cc
class Line::LineImpl {
public:
    LineImpl(int x1, int y1, int x2, int y2);
    void printLine();
private:
    class Point {
    public:
        Point(int ix, int iy) 
        : _ix(ix)
        , _iy(iy)
        {}

        void printPoint() 
        {
            cout << "(" << _ix << ", " << _iy << ")" << endl;
        }
    private:
        int _ix;
        int _iy;
    };
private:
    Point _pt1;
    Point _pt2;
};

Line::LineImpl::LineImpl(int x1, int y1, int x2, int y2)
: _pt1(x1, y1)
, _pt2(x2, y2)
{}

void Line::LineImpl::printLine()
{
    _pt1.printPoint();
    cout << "  ⬇  " << endl; 
    _pt2.printPoint();
}

Line::Line(int x1, int y1, int x2, int y2)
: lineimpl(new LineImpl(x1, y1, x2, y2))
{}

Line::~Line()
{
    if(lineimpl) {
        delete lineimpl;
        lineimpl = nullptr;
    }
}

void Line::printLine() 
{
    lineimpl->printLine();
}

int main(int argc, char* argv[])
{
    Line l(1,1,2,2);
    l.printLine();
    return 0;
}

