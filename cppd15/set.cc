#include <iostream>
#include <string>
#include <set>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::set;

int main(int argc, char* argv[])
{
    // 初始化的方式
    set<string> students;
    /* set<string> students2({"Yuki", "Snow", "Hazuyuki"}); */ 
    set<string> students2{"Yuki", "Snow", "Hazuyuki"};    // student2早期版本常见
    set<string> students3 = {"Yuki", "Snow", "Hazuyuki"};   // √ student3 C++11

    // 插入
    students3.insert("44");

    // 查找
    set<string>::iterator it = students3.find("Snow");
    if(it != students3.end())
    {
        cout << "找到啦！" << *it << endl;
    }

    // 删除(迭代器、迭代器范围、元素键值key)
    students3.erase(it);
    students3.erase(students3.begin(), students3.end()); // 删除区间[first, last)
    students3.erase("Snow");

    // 修改: 不支持修改！

    // 遍历
    for(const auto & str : students3)
    {
        cout << str << endl;
    }

    return 0;
}

