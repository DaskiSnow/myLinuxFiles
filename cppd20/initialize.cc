#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::deque;

int main(int argc, char* argv[])
{
    // 序列式容器的五种初始化方式
    
    // 1. 无参构造
    vector<int> vec; 
    list<int> lst; 
    deque<int> deq; 

    // 2. count个value值(当不填写value时执行对应元素的默认构造)
    int count = 5;
    double value = 3.14;
    vector<int> vec2(count);
    list<int> lst2(count, value);
    deque<int> deq2(count, value);

    // 3. 拷贝构造/移动构造
    vector<int> vec3 = std::move(vec2);
    list<int> lst3 = lst2;
    deque<int> deq3 = deq2;

    // 4. 迭代器范围
    vector<int> vec4(lst2.begin(), lst2.end());
    list<int> lst4(deq2.begin(), deq2.end());
    deque<int> deq4(vec2.begin(), vec2.end());

    // 5. 初始化列表(有啥区别？)
    vector<int> vec5{1, 2, 3, 4};
    vector<int> vec6({1, 2, 3, 4});
    vector<int> vec7 = {1, 2, 3, 4};
    list<int> lst5{1, 2, 3, 4};
    list<int> lst6({1, 2, 3, 4});
    list<int> lst7 = {1, 2, 3, 4};
    deque<int> deq5{1, 2, 3, 4};
    deque<int> deq6({1, 2, 3, 4});
    deque<int> deq7 = {1, 2, 3, 4};

    return 0;
}
