#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

/**
 *  @brief  单例模式自动释放之atexit(destroy)
*/

class Singleton
{
public:
    static Singleton * getInstance()
    {
        if(_pInstance == nullptr)
        {
            _pInstance = new Singleton;
            atexit(destroy);
        }
        return _pInstance;
    }

    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

private:
    static Singleton * _pInstance;
private:
    Singleton()
    : _buf(new char[10]())
    {}

    ~Singleton()
    {
        if(_buf)
        {
            delete [] _buf;
            _buf = nullptr;
        }
    }

private:
    char * _buf;
};
Singleton * Singleton::_pInstance = Singleton::getInstance();    // 饿汉模式: 多线程更安全
// Singleton * Singleton::_pInstance = nullptr;                  // 懒汉模式/饱汉模式: 线程不安全, 若要实现线程安全需要加锁以实现同步

void test()
{
    Singleton * p = Singleton::getInstance();
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

