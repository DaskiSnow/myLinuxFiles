#include <iostream>
#include <string>
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::string;

template<typename T, int kSize = 10>
class Queue
{
    friend void test();
public:
    Queue()
    : _front(0)
    , _rear(0)
    , _size(0)
    , _arr(new T[kSize]())
    {}

    ~Queue()
    {
        if(_arr)
        {
            delete [] _arr;
        }
    }

    bool isEmpty()
    {
        return _size == 0;
    }

    bool isFull()
    {
        return _size == kSize;
    }

    void push(const T & x)
    {
        if(isFull())
        {
            cerr << "Queue is full!" << endl;
            return ;
        }
        _arr[_rear] = x;
        _rear = (_rear + 1) % kSize;
        ++_size;
    }

    T pop()
    {
        if(isEmpty())
        {
            static T nondata;
            cerr << "Queue is empty!" << endl;
            return nondata;
        }
        /* T temp = _arr[_front]; */
        _front = (_front + 1) % kSize;
        --_size;
        return _arr[(_front - 1 + kSize) % kSize];
    }

    T front()
    {
        if(isEmpty())
        {
            static T nondata;
            cerr << "Queue is empty!" << endl;
            return nondata;
        }
        return _arr[_front];
    }

private:
    int _front;
    int _rear;
    int _size;
    T * _arr;
};

void test()
{
    Queue<string, 5> strq;
    cout << strq.pop() << endl;
    strq.push("aaa");
    strq.push("bbb");
    strq.push("ccc");
    strq.push("ddd");
    strq.push("eee");
    cout << strq.front() << endl;
    cout << strq.pop() << endl;
    cout << strq.pop() << endl;
    cout << strq.pop() << endl;
    cout << strq.pop() << endl;
    cout << strq.pop() << endl;
    cout << strq.pop() << endl;
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

