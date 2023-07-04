#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// 实现一个类只能生成栈对象，不能生成堆对象的代码
class Point {
public:
    Point(int x = 0, int y = 0)
    : _ix(x)
    , _iy(y)
    {}
    
    
    
private:
    int _ix;
    int _iy;
    void* operator new(size_t sz);
    void operator delete(void* pointer);
};

int main(int argc, char* argv[])
{
    Point p;  // 创建栈对象
    // Point *pp = new Point;  // error
    return 0;
}

