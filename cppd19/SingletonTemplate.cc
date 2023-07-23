#include <assert.h>
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Point;
class Computer;

// 每个类都有自己的Singleton程序代码，不同类之间互不影响
// 采用单例模式自动释放之内部类
template<typename T> 
class Singleton
{
public:
    template<typename... Args>
    static T * getInstance(Args... args)
    {
        if(_pInstance == nullptr)
        {
            _pInstance = new T(args...); // 提供合法的参数是调用者的职责
            // _ar;   // 原因：静态数据成员在main前初始化了，故无法推导出T，这里是为了推导出T
        }
        return _pInstance;
    }

    // 对于单例模式之内部类来说, 可以不设置destroy
    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
        }
    }
private:
    class AutoRelease
    {
        ~AutoRelease()
        {
            if(Singleton::_pInstance)
            {
                delete _pInstance;
            }
        }
    };

private:
    Singleton();
    ~Singleton();
    static T * _pInstance; 
};

// 注意：这个要在.cpp文件中初始化
template<typename T>
T * Singleton<T>::_pInstance =  nullptr;

class Point
{
friend class Singleton<Point>;
public:
    Point(int ix, int iy)
    : _ix(ix)
    , _iy(iy)
    {}

    void print()
    {
        printf("(%d, %d)\n", _ix, _iy);
    }
private:
    void reset(int ix, int iy)
    {
        _ix = ix;
        _iy = iy;
    }

private:
    int _ix;
    int _iy;
};

class Computer
{
friend class Singleton<Computer>;
public:
    Computer(const string & brand, double price)
    : _brand(brand)
    , _price(price)
    {}

    void print()
    {
        printf("brand: %s, price: %lf\n", _brand.c_str(), _price);
    }

private:

    string _brand;
    double _price;
};

// 两次的AutoRelease的原因: Singleton<T>被实例化了两次, 静态变量会在编译时进行初始化
int main(int argc, char* argv[])
{
    Point * p1 = Singleton<Point>::getInstance(1,2);
    p1->print();
    Point * p2 = Singleton<Point>::getInstance(3,4);
    p2->print();
    Computer * c1 = Singleton<Computer>::getInstance("MI",2);
    c1->print();
    Computer * c2 = Singleton<Computer>::getInstance("HUAWEI",4);
    c2->print();

    cout << (p1 == p2) << endl; // 1
    cout << (c1 == c2) << endl; // 1

    return 0;
}

