#include <string.h>
#include <iostream>
#include <memory>
using namespace std;

template<typename T> 
class Vector 
{ 
friend void test();
friend void test2();
using iterator = T *;
public:     
    Vector()
    : _start(0)
    , _finish(0)
    , _end_of_storage(0)
    {
        // 对具有模板的静态数据成员执行 实例化(疑问: 这里注释了也依然正确执行)
        //_alloc;        
    }

    // destroy + deallocate
    ~Vector()
    {
        // 依次执行对象的析构函数
        _Destroy(_start, _finish);

        // 回收未初始化的空间
        _alloc.deallocate(_start, _end_of_storage - _start);
    }

    iterator begin() const
    {
        return _start;
    }

    iterator end() const
    {
        return _finish;
    }

    void push_back(const T & x)
    {
        if(_finish != _end_of_storage)
        {
            // 未满
            _alloc.construct(_finish, x);
            ++_finish;
        }
        else
        {
            cout << "----触发扩容----" << endl; 
            // 满则扩容再插入
            push_back_aux(x);   
        }
    }

    void pop_back() 
    {
        --_finish;
        _alloc.destroy(_finish);
    }

    int size() const
    {
        return _finish - _start;
    }     

    int capacity() const
    {
        return _end_of_storage - _start;
    }

private:     
    // 两倍扩容策略
    void push_back_aux(const T & x)
    {
        size_t oldSize = size(); 
        size_t len = oldSize != 0 ? 2 * oldSize : 1 ;
        T * new_start = _alloc.allocate(len);
        T * new_finish = new_start;

        /* 关于uninitialized_copy的信息:
         * 复制旧元素到新空间，该函数会根据参数类型来选择不同的复制策略
         * 1：对于char*类型所表示的数据，unintialized_copy->memmove(能处理重叠情况)->memcopy；
         * 2：对于其他类型所表示的数据，unintialized_copy->某个类的实例unintialized_copy_aux；会根据其是否为普通旧数据(POD)来选择直接复制/默认构造/拷贝构造；
         * 结论：不能直接使用memcpy,直接使用memcopy可能会导致数据成员的不正确行为，
         * 比如指针在memcopy后，可能会导致多个对象指向同一片内存空间，或复制后的指针指向一片已被释放的空间
         */ 
        new_finish = uninitialized_copy(_start, _finish, new_finish); // 复制旧元素到新空间
        _alloc.construct(new_finish, x); // 末尾插入新元素
        ++new_finish;

        // 回收旧的堆空间
        _Destroy(_start, _finish); // 依次执行对象的析构函数
        _alloc.deallocate(_start, _end_of_storage - _start); // 回收未初始化的空间(第二个参数是元素个数，而非字节数)

        // 更新"三指针"
        _start = new_start;
        _finish = new_finish;
        _end_of_storage = new_start + len;
        
    }
private:         
    static std::allocator<T> _alloc;          
    T *_start;                 //指向数组中的第一个元素     
    T *_finish;                //指向最后一个实际元素之后的那个元素     
    T *_end_of_storage;        //指向数组本身之后的位置 
};
template<typename T>
std::allocator<T> Vector<T>::_alloc;

void test()
{
    Vector<int> vecInt; 
    vecInt.push_back(1);
    vecInt.push_back(2);
    vecInt.push_back(3);
    vecInt.push_back(4);
    vecInt.push_back(5);
    cout << "size = " << vecInt.size() << endl;
    cout << "capacity = " << vecInt.capacity() << endl;
    cout << "----print----" << endl;
    for(int * p = vecInt._start; p != vecInt._finish; ++p)
    {
        cout << *p << endl;
    }
    
    cout << endl;
    vecInt.pop_back();
    vecInt.pop_back();
    vecInt.pop_back();
    cout << "size = " << vecInt.size() << endl;
    cout << "capacity = " << vecInt.capacity() << endl;
    cout << "----print----" << endl;
    for(int * p = vecInt._start; p != vecInt._finish; ++p)
    {
        cout << *p << endl;
    }
}

// 无内存泄露
void test2()
{
    Vector<string> vecInt; 
    vecInt.push_back("AA");
    vecInt.push_back("BB");
    vecInt.push_back("CC");
    vecInt.push_back("DD");
    vecInt.push_back("EE");
    cout << "size = " << vecInt.size() << endl;
    cout << "capacity = " << vecInt.capacity() << endl;
    cout << "----print----" << endl;
    for(string * p = vecInt._start; p != vecInt._finish; ++p)
    {
        cout << *p << endl;
    }
    
    cout << endl;
    vecInt.pop_back();
    vecInt.pop_back();
    vecInt.pop_back();
    cout << "size = " << vecInt.size() << endl;
    cout << "capacity = " << vecInt.capacity() << endl;
    cout << "----print----" << endl;
    for(string * p = vecInt._start; p != vecInt._finish; ++p)
    {
        cout << *p << endl;
    }
}

class MyClass
{
public:
    MyClass(const char * str)
    {
        cout << "MyClass(const char * str), _buf = " << str <<endl;
        if(str)
        {
            _buf = new char[strlen(str) + 1]();
            strcpy(_buf, str);
        }
    }

    MyClass(const MyClass & obj)
    {
        // 深拷贝
        cout << "MyClass(const MyClass & obj), _buf = " << obj._buf << endl;
        if(obj._buf)
        {
            _buf = new char[strlen(obj._buf) + 1]();
            strcpy(_buf, obj._buf);
        }
    }

    ~MyClass()
    {
        if(_buf)
        {
            cout << "~MyClass(), _buf = " << _buf << endl;
            delete [] _buf;
        }
    }
private:
   char * _buf; 
};

// 无内存泄露
void test3()
{
    cout << "--------开始push_back--------" << endl;
    Vector<MyClass> vecInt; 
    vecInt.push_back("AA");
    vecInt.push_back("BB");
    vecInt.push_back("CC");
    vecInt.push_back("DD");
    vecInt.push_back("EE");
    cout << "--------push_back完成--------" << endl;
    cout << "size = " << vecInt.size() << endl;
    cout << "capacity = " << vecInt.capacity() << endl;
    
    cout << endl;
    cout << "--------开始pop_back--------" << endl;
    vecInt.pop_back();
    vecInt.pop_back();
    vecInt.pop_back();
    cout << "--------pop_back完成--------" << endl;
    cout << "size = " << vecInt.size() << endl;
    cout << "capacity = " << vecInt.capacity() << endl;
}


int main(int argc, char* argv[])
{
    //test();
    //test2();
    test3();
    return 0;
}

