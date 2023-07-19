#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

/**
 *  @brief  单例模式自动释放之内部类
*/

class Singleton
{
public:
    static Singleton * getInstance()
    {
        if(_pInstance == nullptr)
        {
            _pInstance = new Singleton;
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
    class AutoRelease
    {
    // 注意这里要public嚄
    public:
        ~AutoRelease()
        {
            if(_pInstance)
            {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };

    static Singleton * _pInstance;
    static AutoRelease ar;

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

// 静态数据成员记得在类外初始化
Singleton * Singleton::_pInstance = nullptr; // 懒汉模式/饱汉模式
Singleton::AutoRelease Singleton::ar;


int main(int argc, char* argv[])
{
    Singleton * p = Singleton::getInstance();
    return 0;
}

