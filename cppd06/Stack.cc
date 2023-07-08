#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// 编写一个类，实现简单的栈。
// 并自行写出测试用例，每个函数都需要测试到。
class Stack {
public:
    Stack(int stackSize) 
    : _top(-1)
    , _stackSize(stackSize)
    , _arr(new int[stackSize]())
    {}
    
    Stack(const Stack & s)
    : _stackSize(s._stackSize)
    , _arr(new int[s._stackSize]())
    {
        for(int i = 0; i < s._stackSize; i++) {
            _arr[i] = s._arr[i];
        }
    }

    Stack & operator=(const Stack & s) {
        if(this == &s) return *this;
        delete [] _arr;
        _arr = new int[s._stackSize];
        for(int i = 0; i < s._stackSize; i++) {
            _arr[i] = s._arr[i];
        }
        _stackSize = s._stackSize;
        _top = s._top;
        return *this;
    }

    // 注意习惯，判断和置空指针 !
    ~Stack() {
        if(_arr) {
            delete [] _arr;
            _arr = nullptr;
        }
    }

    //判断栈是否为空
    bool empty() const {
        return _top == -1;
    }	

    //判断栈是否已满
    bool full() const {
        return _top == _stackSize - 1;
    }	

    //元素入栈
    void push(int x) {
        if(full()) return ;
        _arr[++_top] = x;
        return ;
    } 

    //元素出栈
    int pop() {
        if(empty()) return -1; // 假设不存在-1的元素，表示错误
        return _arr[_top--];
    }     

    //获取栈顶元素
    int top() const{
        if(empty()) return -1; // 用来表示错误
        return _arr[_top];
    }		

private:
    int _top;
    int _stackSize;
    int* _arr; // 整型数组
};

int main(int argc, char* argv[])
{
    Stack s(3);
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "empty =  " << s.empty() << endl;
    cout << "full =  " << s.full() << endl;
    cout << "pop = " << s.pop() << endl;
    cout << "top = " << s.top() << endl;
    cout << "pop = " << s.pop() << endl;
    cout << "pop = " << s.pop() << endl;
    cout << "empty =  " << s.empty() << endl;

    return 0;
}

