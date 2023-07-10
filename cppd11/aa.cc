#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
// 重载运算符+

class MyInteger {
public:
    MyInteger(int value = 0)
    : _value(value)
    {}

    int operator()(const MyInteger & rhs = MyInteger(100)) 
    {
        return _value + rhs._value;    
    }

    int operator+(const MyInteger & rhs) 
    {
        return _value + rhs._value;
    }

private:
    int _value;
};

void test()
{
    vector<int> vecInt;
    vecInt.push_back(10);
    vecInt.push_back(20);
    vecInt.push_back(30);
    vector<int>::iterator it;
    for(it = vecInt.begin(); it != vecInt.end(); ++it)
    {
        if(*it == 20)
        {
            break;
        }
    }
    vecInt.insert(it, 10, 0);
    for(it = vecInt.begin(); it != vecInt.end(); ++it)
    {
        cout << *it << endl;

    }
}

// Lambda表达式探索
void test2()
{
    vector<int> vecInt;
    vecInt.push_back(23);
    vecInt.push_back(13);
    vecInt.push_back(3);
    vecInt.push_back(2);
    vecInt.push_back(66);

    // 升序排序int数组
    auto ascOrder = [](int a, int b){return a < b;}; 
    // 第三参数类型：函数指针/函数对象
    stable_sort(vecInt.begin(), vecInt.end(), ascOrder);
    for(const auto & i : vecInt)
    {
        cout << i << endl;
    }

}

const int & func(int & a, int & b) 
{
    a = 2;
    return a;
}

class MyClass {
public:
    int get_value() const { // 常量成员函数，不能修改数据成员
        // m_value = 0; // 错误，不能修改数据成员
        return m_value;
    }

    void print_value(string & prefix) const { // 常量成员函数，不能修改引用参数
        cout << prefix << m_value << endl;
        prefix = "new_prefix"; // 错误，不能修改引用参数
    }

private:
    int m_value;
};

int main(int argc, char* argv[])
{
    MyClass myobj;
    string str = "STR1";
    myobj.print_value(str);
    cout << str << endl;
    return 0;
}

