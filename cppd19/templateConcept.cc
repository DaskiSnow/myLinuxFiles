#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

// 函数模板1 
template<typename T, typename K>  
T add(T x, K y){}

// 全特化(函数模板1)
template<>           
const char * add(const char * x, const char * y){}

/*函数模板不允许偏特化*/

// 以函数模板的形式重载(函数模板2)
template<typename T, typename K, typename L> 
L add(T x, K y){}

// 以普通函数的形式重载
void add(void){} 

// 模板参数类型: 类型参数、非类型参数(整型√  浮点型×)
template<typename T, bool b, char ch, size_t s>
T add(T x){ cout << b << ch << s << endl; }

// 可变模板参数(...在变量左侧是"封包" ...在变量右侧是"解包")
// 其中typename/class... Args, Args被称为模板参数包
// Args... args, args被称为函数参数包
// 递归函数展开参数包
double sum()
{
    return 0;
}
template<typename T, typename... Args>
T sum(T x, Args... args)
{
    return x + sum(args...);
}
// cout << sum(1, 2.2, 3, 4) << endl;

// 参数列表+逗号表达式展开参数包
template<typename... Args>
double sum2(Args... args)
{
    double arr[] = {args...};
    double res = 0;
    for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
    {
        res += arr[i];
    }
    return res;
}

// 求可变模板参数的长度
template<typename... Args>
void sum3(Args... args)
{
    cout << sizeof...(Args) << endl; // 6
    cout << sizeof...(args) << endl; // 6
}

// 嵌套模板的定义写法
template<typename T>
class Stack
{
private:
    template<typename K>
    class Inner
    {
        template<typename P>   
        void func(P x);
    };
};
template<typename T>
template<typename K>
template<typename P>
void Stack<T>::Inner<K>::func(P x)
{}

int main(int argc, char* argv[])
{
    cout << sum2(1,2,3,4,3.4) << endl;
    return 0;
}

