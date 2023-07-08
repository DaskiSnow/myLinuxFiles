#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Line {
public:
    static Line * getInstance(int x1, int y1, int x2, int y2);
    void printLine();
private:
    class Point 
    {
    public:
        friend class Line;
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
    
    class AutoRelease
    {
        ~AutoRelease() 
        {
            if(_pInstance) {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };
private:
    Line(int x1, int y1, int x2, int y2);
    ~Line();
private:
    Point * _pt1;
    Point * _pt2;
    static Line * _pInstance;
    static AutoRelease _ar;  // 用于程序结束时，自动释放单例对象
};

Line * Line::_pInstance = nullptr;

Line * Line::getInstance(int x1, int y1, int x2, int y2) 
{
    if(_pInstance == nullptr) 
    {
        _pInstance = new Line(x1, y1, x2, y2);
        return _pInstance;
    }

    _pInstance->_pt1->_ix = x1;
    _pInstance->_pt1->_iy = y1;
    _pInstance->_pt2->_ix = x2;
    _pInstance->_pt2->_iy = y2;
    return _pInstance;
}


Line::Line(int x1, int y1, int x2, int y2)
: _pt1(new Point(x1, y1))
, _pt2(new Point(x2, y2))
{}

Line::~Line() 
{
    if(_pt1) 
    {
        delete _pt1;
        _pt1 = nullptr;
    }
    if(_pt2)
    {
        delete _pt2;
        _pt2 = nullptr;
    }
}

void Line::printLine()
{
    _pt1->printPoint();
    cout << "  ⬇  " << endl; 
    _pt2->printPoint();
}

int main(int argc, char* argv[])
{
    Line * l = Line::getInstance(1,2,3,4);
    l->printLine();
    return 0;
}

