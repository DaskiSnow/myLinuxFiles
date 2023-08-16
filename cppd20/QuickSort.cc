#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// 使用模板实现快速排序算法
// less<T>一般指示升序、greater<T>一般指示降序
// less<T>类重载了函数调用符函数, 该函数return (T1 < T1), 这要求T类型需要重载<运算符函数
// greater<T>同理
template<typename T, typename Compare=std::less<T>> 
class MyQsort 
{ 
public:     
    MyQsort(T *arr, size_t size)
    : _vec(arr, arr + size)
    , _com(Compare())
    {}

    void quick(int left, int right)
    {
        if(left >= right) return;
        int p = partition(left, right);
        quick(left, p - 1);
        quick(p + 1, right);
    }

    int partition(int left, int right)
    {
        T pivot = _vec[right]; 
        int store_idx = left;
        int i = left;
        while(i <= right)
        {
            if(_com(_vec[i], pivot))   // < 或 >
            {
                swap(_vec[store_idx], _vec[i]);
                ++store_idx;
            }
            ++i;
        } // i == right
        swap(_vec[store_idx], _vec[right]);
        return store_idx;
    }

    void print() // 需要T类型重载了<<
    {
        for(const auto & i : _vec)
        {
            cout << i << endl;
        }
    }
private:
    void swap(T & x, T & y)
    {
        T temp = x;
        x = y;
        y = temp;
    }
private:    
    vector<T> _vec; 
    Compare _com;
};

int main(int argc, char* argv[])
{
    int arr[10] = {1 ,9, 2, 5, 6, 87, 55, 33, 21, 11};
    MyQsort<int, std::greater<int>> mq(arr, 10);    
    mq.print();
    mq.quick(0, 9);
    cout << "-------------------" << endl;
    mq.print();
    return 0;
}

