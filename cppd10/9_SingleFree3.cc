#include <iostream>
#include <string>
#include <pthread.h>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class SingleBase {
public:
    static SingleBase * getInstance()
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

    static void init() 
    {
        _pInstance = new SingleBase;
        atexit(destroy);

    }
private:
    SingleBase(int bufSize = 128)
        : _buf(new char[bufSize]())
    {}

    ~SingleBase()
    {
        delete [] _buf;
    }
    char * _buf;
private:
    static SingleBase * _pInstance;
    static pthread_once_t _once;
};

// 静态成员的初始化
SingleBase * SingleBase::_pInstance = nullptr;
pthread_once_t SingleBase::_once = PTHREAD_ONCE_INIT;

int main(int argc, char* argv[])
{
    SingleBase * sb = SingleBase::getInstance();
    return 0;
}

