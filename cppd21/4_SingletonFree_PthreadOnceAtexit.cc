#include <pthread.h>
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

/**
 *  @brief  单例模式自动释放之pthread_once + atexit(存在平台问题: 仅限于Linux)
 *  链接时 -lpthread
*/

class Singleton
{
public:
    static Singleton * getInstance()
    {
        pthread_once(&_once, init);        
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
    static void init()
    {
        if(_pInstance == nullptr)
        {
            _pInstance = new Singleton;
            atexit(destroy);
        }
    }
    static Singleton * _pInstance;
    static pthread_once_t _once;

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
Singleton * Singleton::_pInstance = nullptr; // 懒汉模式/饱汉模式
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

void test()
{
    Singleton * p = Singleton::getInstance();
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

