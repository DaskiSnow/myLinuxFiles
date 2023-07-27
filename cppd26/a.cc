#include <iostream>
#include <string>
#include <functional>
#include <iterator>
#include <algorithm>
#include <set>
#include <list>
#include <tuple>
using namespace std;

class Point
{
public:
    Point(int x, int y)
    : _ix(x)
    , _iy(y)
    {}


    void print()
    {
        printf("(%d, %d)\n", _ix, _iy);
    }

    static void printStatic()
    {
        printf("printStatic\n");
    }

    void reset(int x, int y, string & str)
    {
        _ix = x;
        _iy = y;
        str = "what?";
    }

    int _ix;
    int _iy;
};

// bind的练习
int sum(int a, int b, int c)
{
    return a + b + c;
}

// bind的原理？？
void test()
{
    // 对于函数对象的传递：普通成员函数-加&, static成员函数-随缘
    // 对于对象的传递: 加&则引用传递, 不加则值传递(更安全, 但效率差些)
    // 对于参数的传递: 加std::ref/std::cref则引用/常引用传递，否则默认值传递(建议:都加引用包装包装器)
    Point p(1, 2);
    string str = "Hello";
    using namespace std::placeholders;
    auto f2 = bind(&Point::reset, &p, _1, _2, std::ref(str));
    f2(3, 4);
    cout << str << endl;
    p.print();

    // bind 可以绑定public数据成员
    auto y = bind(&Point::_iy, &p);
}

// ostream_iterator 的练习
void test2()
{
    ostream_iterator<string> osi(cout, " | ");    
    osi = "first string";  // 底层：cout << "first string";
    osi = "second string";
    osi = "third string";
    cout << endl;

    ostream_iterator<string> osi2(cout, "\n");
    vector<string> strVec = {"你当我是浮夸吧", "夸张只因我很怕"}; 
    copy(strVec.begin(), strVec.end(), osi2); // 底层: 不断调用=
}

// istream_iterator 的练习, 还挺妙
void test3()
{
    istream_iterator<int> isi(cin);
    int a = *isi;
    ++isi;
    int b = *isi;
    cout << a << " " << b << endl;
}

// back_insert_iterator 的练习: 把it抽象成一个指向end()位置的指针!
void test4()
{
    vector<int> intVec = {1, 2, 3, 4};
    ostream_iterator<int> coutIt(cout, " ");
    back_insert_iterator<vector<int>> vecBIIt(intVec);
    auto vecBIIt2 = back_inserter(intVec); // 返回类型 "back_insert_iterator<vector<int>>"
    
    *vecBIIt = 5;  // 等价于 intVec.push_back(5);
    *vecBIIt = 6;
    *vecBIIt = 7;
    *vecBIIt2 = 100;

    copy(intVec.begin(), intVec.end(), coutIt);
    cout << endl;
}

// inserter
void test5()
{
    list<int> lst = {1, 2, 3, 4};
    auto it2st = inserter(lst, ++lst.begin());
    *it2st = 5;
    *it2st = 6;

    copy(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    // output:1 5 6 2 3 4
}

void test6()
{
    auto t = make_tuple(2018, 22, "Yuki");
    cout << tuple_size<decltype(t)>::value << endl; 
    cout << get<0>(t) << endl;
}

// 容器适配器priority_queue练习
void test7()
{

}

int main(int argc, char* argv[])
{
    test6();
    return 0;
}

