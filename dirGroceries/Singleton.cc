#include <func.hh>

using namespace std;

/**
 *  @brief 单例模式例子(线程安全 + 自动释放)
 */
class Singleton
{
public:
    static Singleton * getInstance()
    {
        pthread_once(&once, init);
        return _pInstance;
    }

    static void destroy()
    {
        if(_pInstance)
        {
            delete  _pInstance;
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

private:
    Singleton()
    {
        cout << "Singleton()" << endl;
    }
    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }

private:
    static Singleton * _pInstance;
    static pthread_once_t once;
};
Singleton * Singleton::_pInstance = nullptr;         // 饿汉模式
/* Singleton * Singleton::_pInstance = new Singleton(); // 饱汉模式 */
pthread_once_t Singleton::once = PTHREAD_ONCE_INIT;

void test()
{
    Singleton * singleton = Singleton::getInstance();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

