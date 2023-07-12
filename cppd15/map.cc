#include <iostream>
#include <string>
#include <map>
#include <utility>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;
using std::pair;
using std::make_pair;

// 所需头文件和实体
// <map>
// <utility> 
// std::map
// std::pair 
// std::make_pair
int main(int argc, char* argv[])
{
    // 三种在初始化列表中, 给map赋初始值的方式，最外为花括号
    // {}, pair<>, make_pair()
    map<int, string>students
    {
        {0, "Yuki"}
        , pair<int, string>(1, "Snow")
        , make_pair(2, "Xue")
    };

    // 插入(.insert(pair的三种方式), 下标[])
    students.insert({3, "33"});
    students.insert(pair<int, string>(4, "44"));
    students.insert(make_pair(5, "55"));
    students[6] = "Hazuyuki";

    // 查找(.find()、下标[])
    map<int, string>::iterator it = students.find(2);
    cout << it->second << endl;
    cout << students[2] << endl;

    // 删除(.erase(三种方式))  迭代器、迭代器范围、键值key
    students.erase(it);
    students.erase(students.begin(), students.end());
    students.erase(0);

    // 修改
    students[4] = "changed content";  // 前提：[4]存在

    // 遍历(普通for、范围for)
    for(map<int, string>::iterator it = students.begin(); it != students.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }

    for(auto it = students.begin(); it != students.end(); ++it) 
    {
        cout << it->first << " " << it->second << endl;
    }

    for(const pair<int, string> & p : students )
    {
        cout << p.first << " " << p.second << endl;
    }

    for(const auto & p : students) 
    {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}

