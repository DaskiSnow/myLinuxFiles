#include <func.hh>

using namespace std;

void swap(int & a, int & b)
{
    if(a == b) return;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

// pay attention: n is changed
void heapify(int arr[], int i, int n)
{
    if(n <= 1) return;
    int maxIdx = i;
    int lIdx = 2 * i + 1;
    int rIdx = 2 * i + 2;
    if(arr[lIdx] > arr[maxIdx]) maxIdx = lIdx;
    if(arr[rIdx] > arr[maxIdx]) maxIdx = rIdx;
    if(maxIdx != i)
    {
        swap(arr[maxIdx], arr[i]);
        heapify(arr, maxIdx, n);
    }
}

void heapSort(int arr[], int n)
{
    // 1. 建堆
    for(int i =(n - 1)/ 2; i >= 0; --i)
    {
        heapify(arr, i, n);
    }

    // 2. 调整堆
    for(int i = 0; i < n - 2; ++i)
    {
        swap(arr[0], arr[n - 1 - i]);
        heapify(arr, 0, n - 1 - i);
    }

}

int main(int argc, char *argv[])
{
    return 0;
}

