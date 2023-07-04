#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Point {
public:
    Point(int ix = 1, int iy = 1)
    : _ix(ix)
    , _iy(iy)
    {
        cout << "Point ix = " << ix << " iy = " << iy <<endl;
    }

    
    // 拷贝构造函数
    Point(const Point & point) 
    : _ix(point._ix)
    , _iy(point._iy)
    {
        
        cout << "Point(const Point & point)" << endl;
    }

    // 赋值运算符函数(4部曲)
    Point & operator=(const Point & point) {
        cout << "Point & operator=(const Point & point)" << endl;
        return *this;
    }

    ~Point() {
        delete this;
        cout << "~Point" << endl;
    }

    void print(){
        cout << "_ix = " << _ix << ", _iy = " << _iy << endl;
    }

private:
    int _ix;
    int _iy;
};

// 对象数组的测试
int main(int argc, char* argv[])
{
    string str;
    string str2(3,'a');
    cout << str2 << endl;
    cout << str2.empty() << endl;
    cout << str2.length() << endl;

    string str3(str2, 0, 2);
    cout << str3 << endl;

    const char * cstr = "hello";
    string str4(cstr);
    cout << str4 << endl;
    
    // 重点：append()

    // string的遍历:
    // 普通for循环：for(int idx = 0; idx < str.length(); idx++) { str[idx]; }
    // 增强for循环：for(auto & ch : str){ cout << ch << endl; }
    // for+迭代器(广义的指针): for(auto it = str.begin(); it != str.end(); it++) { *it; } 
    
    // 截取字串：substr()
    


    //// 不能显式调用构造函数，自动调用无参/所有参数为缺省值的构造
    //Point * point_arr = new Point[5]();

    //for(Point *p = point_arr; p < point_arr + 5; p++) {
    //    p->print();
    //}
    //for(int i = 0; i < 5; i++) {
    //    point_arr[i].print();
    //}

    //delete [] point_arr;

    //Point point(3,3);
    //// {1,1}调用构造
    //// Point(2,2)调用构造(+拷贝构造+析构，若不优化)
    //// point调用拷贝构造
    //Point point_arr[3] = {{1,1}, Point(2,2), point};

    return 0;
}

