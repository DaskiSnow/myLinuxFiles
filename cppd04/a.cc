#include <iostream>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;

class Point{

public:
    Point(int x = 0, int y = 0)
    : _ix(x)
    , _iy(y)
    {

        cout << "构造函数Point" << endl;
    }
    // 拷贝构造函数
    Point(const Point & point)
    : _ix(point._ix)
    , _iy(point._iy)
    {
        cout << "拷贝构造函数Point" << endl;

    }

    // 赋值运算符函数
    Point & operator=(const Point & point) {
        cout << "赋值运算符函数Point"  << endl;
        _ix = point._ix;
        _iy = point._iy;
        return *this;
    }

    ~Point() {
        cout << "析构函数Point" << endl;
    }

private:
    int _ix;
    int _iy;

};

class Student {
public:
    // 构造函数
    Student(int num, const char* name, const Point & point)
    : _num(num)
    , _name(new char[strlen(name) + 1])
    , _point1(point)
    {
        cout << "Student(int num, const char* name)" << endl;
        strcpy(_name, name);
        
    }

    // 拷贝构造函数
    Student(const Student & s, const Point & point)
    : _num(s._num + 1)
    , _name(new char[strlen(s._name) + 1])
    , _point1(point)
    {
        strcpy(_name, s._name);
        cout << "Student(const Student & s)" << endl;
    }

    // 赋值运算符函数
    Student & operator=(const Student & s) {
        cout << "Student & operator=(const Student & s)" << endl;
        // 1.判断自复制情况
        if(this == &s) return *this;
        // 2.释放左操作数的堆空间
        delete [] _name;
        // 3.深拷贝
        _num =  s._num + 10;
        _name = new char[strlen(s._name) + 1];
        strcpy(_name, s._name);
        // 3.返回*this
        return *this;
    }

    // 析构函数
    ~Student() {
        delete [] _name;
    }

    // const 成员函数
    int get_staticInt() const{
        printf("const\n");
        static_int++;
        return static_int;
    }
    
    // 重载
    int get_staticInt() {
        printf("非const\n");
        static_int--;
        return static_int;
    }
     
private:
    int _num;
    char* _name;

    const Point & _point1;
    static int static_int;
};

int Student::static_int = 1;

int main(int argc, char* argv[])
{
    Point point(1, 2);
    Student xue(1, "xue", point);
    cout << "xue.get_staticInt() = " <<xue.get_staticInt() << endl;
    // const Student *pxue = &xue;
    const Student & cxue = xue;
    cout << "const xue.get_staticInt() = " <<cxue.get_staticInt() << endl;
    cout << "const xue.get_staticInt() = " <<cxue.get_staticInt() << endl;
    cout << "const xue.get_staticInt() = " <<cxue.get_staticInt() << endl;
    return 0;
}

