#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Base
{
public:
    virtual
    void print()
    {
        cout << "Base::print()" << endl;
    }
};


class Derived
: public Base
{
public:
    void print()
    {
        cout << "Derived::print()" << endl;
    }
};

void fun(Base & br)
{
    br.print();
}

int main(int argc, char* argv[])
{
    Derived derived;
    fun(derived);
    return 0;
}

