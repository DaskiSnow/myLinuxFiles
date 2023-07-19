#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// 模板实现堆排序算法
template <typename T, typename Compare = std::less<T>> 
class HeapSort 
{ 
public:  
    HeapSort(T *arr, size_t size, Compare com)
    : _vec(arr, arr + size)
    {
        sort(com);
    }

    void print()
    {
        for(const auto & x : _vec)
        {
            cout << x << endl;
        }
    }

private:
    void heapify(size_t k, size_t n, Compare &com)
    {
        size_t lIdx = 2 * k + 1; 
        size_t rIdx = 2 * k + 2; 
        size_t largeIdx = k;
        if(lIdx < n && !com(_vec[lIdx], _vec[largeIdx]))
        {
            largeIdx = lIdx;
        }
        if(rIdx < n && !com(_vec[rIdx], _vec[largeIdx]))
        {
            largeIdx = rIdx;
        }
        if(largeIdx != k)
        {
            swap(k, largeIdx);
            heapify(largeIdx, n, com);
        }
    }

    void sort(Compare &com)
    {
        size_t n = _vec.size();
        // 建堆(less-小根堆 greater-大根堆)
        // 注意：这里因为size_t，判断条件要加i < n，否则 i 为递减为负数后变成一个极大的数, 导致死循环
        for(size_t i = (n - 2) / 2; i >= 0 && i < n; --i)   
        {
            heapify(i, n, com);
        }

        // 排序
        for(ssize_t j = n - 1; j > 0; --j)
        {
            swap(j, 0);
            heapify(0, j, com);
        } }
    void swap(size_t idx1, size_t idx2)
    {
        T temp = _vec[idx1];
        _vec[idx1] = _vec[idx2];
        _vec[idx2] = temp;
    }
private:  
    vector<T> _vec; 
};

int main(int argc, char* argv[])
{
    int arr[10] = {23,56,2,12,556,84,12,0,23,21};
    HeapSort<int> hs(arr, 10, std::less<int>()); 
    hs.print();
    return 0;
}

