#include <iostream>

using std::cout;
using std::endl;

// 智能指针的原型: 利用栈对象的生命周期管理资源
template <typename T>
class RAII
{
public:
    //1、在构造函数中初始化资源（托管资源）
    RAII(T *pdata)
    : _pdata(pdata)
    {
        cout << "RAII(T *)" << endl;
    }

    //2、在析构函数中释放资源
    ~RAII()
    {
        cout << "~RAII()" << endl;
        if(_pdata)
        {
            delete _pdata;
            _pdata = nullptr;
        }
    }
    //3、不允许复制或者赋值
    RAII(const RAII &rhs) = delete;
    RAII &operator=(const RAII &rhs) = delete;

    //4、提供若干访问资源的方法
    T *get() const
    {
        return _pdata;
    }

    T *operator->()
    {
        return _pdata;
    }

    T &operator*()
    {
        return *_pdata;
    }

    void reset(T *data)
    {
        if(_pdata)
        {
            delete _pdata;
            _pdata = nullptr;
        }
        _pdata = data;
    }
private:
    /* int *_pdata; */
    /* double *_pdata; */
    /* long *_pdata; */
    T *_pdata;
};

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {
        cout << "Point(int = 0, int = 0)" << endl;
    }

    void print() const
    {
        cout << "(" << _ix 
             << ", " << _iy
             << ")" << endl;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test()
{
    /* RAII<int> raii(new int(10)); */
    /* raii.get(); */
    //利用了栈对象的生命周期管理资源
    RAII<Point> raii(new Point(1, 2));//raii是栈对象
    raii->print();
}
int main(int argc, char *argv[])
{
    test();
    return 0;
}


