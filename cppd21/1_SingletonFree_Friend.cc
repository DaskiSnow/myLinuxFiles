#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

/**
 *  @brief  单例模式自动释放之友元类  
*/
template<typename T> 
class AutoRelease;

class Singleton_String
{
friend class AutoRelease<Singleton_String>;
public:
    static Singleton_String * getInstance()
    {
        if(_pInstance == nullptr)
        {
            _pInstance = new Singleton_String;
        }
        return _pInstance;
    }

    // 可以不写destroy
    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

private:
    static Singleton_String * _pInstance;

private:
    Singleton_String()
    : _buf(new char[10]())
    {}

    ~Singleton_String()
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

Singleton_String * Singleton_String::_pInstance = nullptr; // 懒汉模式/饱汉模式

// 这里自己做了通用性上的改进
template<typename T>
class AutoRelease
{
public:
    AutoRelease(T * pInstance)
    : _pInstance(pInstance)
    {}

    ~AutoRelease();
    T * _pInstance;
};

template<typename T>
AutoRelease<T>::~AutoRelease()
{
    if(_pInstance)
    {
        delete _pInstance;
        _pInstance = nullptr;
    }
}

int main(int argc, char* argv[])
{
    Singleton_String * p = Singleton_String::getInstance();
    AutoRelease<Singleton_String> ar(p);

    return 0;
}

