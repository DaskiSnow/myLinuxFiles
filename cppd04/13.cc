#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Student {
public:
    Student(int num, const char* name, int age)
    : _num(num)
    , _age(age)
    , _name(new char[strlen(name) + 1]()) // 带括号才会被初始化!
    {
        strncpy(_name, name, strlen(name));
    }
        
    void print() {
        cout << "num = " << _num << endl;
        cout << "name = " << _name << endl;
        cout << "age = " << _age << endl;
    }

    ~Student(){
        delete [] _name;
    }

private:
    int _num;
    int _age;
    char* _name;
};

int main()
{
    Student xiaoWang(201865536, "xiaoWang", 23);
    xiaoWang.print();
    return 0;
}

