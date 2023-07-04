#include <iostream>
using std::cout;
using std::endl;

class Singleton {
public:
    static Singleton * getInstance() {
        if(_pInstance == nullptr) { 
            _pInstance = new Singleton;
        }
        return _pInstance;
    }

    static void destroy() {
        if(_pInstance) {
            delete _pInstance;
            _pInstance = nullptr; // 防止double free问题
        }
    }
private:
    Singleton() {
        cout << "Singleton()" << endl;
    }

    ~Singleton() {
        cout << "~Singleton()" << endl;
    }

    static Singleton * _pInstance;
        
};
// 静态数据成员的初始化
Singleton * Singleton::_pInstance = nullptr;

int main()
{
    Singleton * p1 = Singleton::getInstance();
    Singleton * p2 = Singleton::getInstance();
    cout << p1 << endl;
    cout << p2 << endl;
    Singleton::destroy();
    Singleton::destroy();
    
    return 0;
}

