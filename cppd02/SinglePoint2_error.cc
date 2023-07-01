#include <iostream>
using std::cout;
using std::endl;

class Point{

    /* Point(){ */
    /*     cout << "Point()" << endl; */
    /* }; */
public:
    static Point * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new Point(0,0);
        }
        return _pInstance;
    }

    void init(int x,int y){
        _ix = x;
        _iy = y;
    }
private:
    Point(int x,int y)
    : _ix(x) //_ix = x;
    , _iy(y) //_iy = _ix;
    {
        cout << "Point(int,int)" << endl;
    }
#if 0
private:
    Point(const Point & rhs)
    : _ix(rhs._ix)
    , _iy(rhs._iy)
    {
        cout << "Point(const Point &)" << endl;
    }

    //在类中所有成员函数都有一个隐含的this指针
    //this代表的是当前对象
    //在编译之后，编译器会自动加上该指针
    //位置：参数中的第一位
    //形式：Point * const this
    Point& operator=(const Point & rhs){
        this->_ix = rhs._ix;
        this->_iy = rhs._iy;
        cout << "Point & operator=(const Point &)" << endl;
        return *this;
    }
#endif
    //意义明确，C++11
    Point & operator=(const Point & rhs) = delete;
    Point(const Point & rhs) = delete;

public:
    void print() const{
        cout << "(" << _ix 
            << "," << _iy 
            << ")" << endl;
    }

    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
private:
    int _ix ;
    int _iy ;
    static Point * _pInstance;
};

Point * Point::_pInstance = nullptr;

void test0(){
    Point * pt = Point::getInstance();
    pt->init(1,2);
    pt->print();
    cout << pt << endl;

    Point * pt2 = Point::getInstance();
    pt->init(3,4);
    pt2->print();
    cout << pt2 << endl;

    pt->print();
    /* delete pt; */
    Point::destroy();

}

int main(void){
    test0();
    cout << "over" << endl;
    return 0;
}

