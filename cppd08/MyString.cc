#include <iostream>
#include <string>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;
using std::string;                             

class String
{
public:
	String()
    : _pstr(nullptr){}

    String(const char *pstr) 
    : _pstr(new char[strlen(pstr)+1]())
    {
         strcpy(_pstr, pstr);
    }

	String(const String &rhs)
    : _pstr(new char[rhs.length()+1])
    {
        strcpy(_pstr, rhs.c_str());
    }

    String &operator=(const String &rhs) {
        if(this == &rhs) return *this;
        delete [] _pstr;
        _pstr = new char[rhs.length()+1]();
        strcpy(_pstr, rhs.c_str());
        return *this;
    }

    ~String() {
        if(_pstr != nullptr) {
            delete [] _pstr;
        }
    }

    void print() const {
        if(_pstr!=nullptr) {
            printf("%s\n", _pstr);
        }
    }

    size_t length() const {
        return strlen(_pstr);
    }
    const char * c_str() const {
        return _pstr;
    }

private:
    char * _pstr;
};


int main()
{
    String str1;
    str1.print();


    String str2 = "Hello,world";
    String str3("wangdao");

    str2.print();   // Hello,world		
    str3.print();	// wangdao

    String str4 = str3;
    str4.print();   // wangdao

    str4 = str2;
    str4.print();   // Hello,world

    return 0;
}


