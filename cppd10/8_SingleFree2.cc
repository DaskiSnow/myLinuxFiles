#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class SingleBase {
public:
    static SingleBase * getInstance()
    {
        if(_pInstance == nullptr) 
        {
            _pInstance = new SingleBase;
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
};

SingleBase * SingleBase::_pInstance = nullptr;

int main(int argc, char* argv[])
{
    SingleBase * sb = SingleBase::getInstance();
    return 0;
}

