#include <func.hh>
#include <stdlib.h>
#include <time.h>

using namespace std;

// 注意: 如果a==b, a ^ b = 0;
void swap(int & a, int & b)
{
    if(a == b) return;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void swap2(int & a, int & b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high)
{
    // 随机选取一个
    srand(clock());
    int randIdx = low + rand() % (high - low + 1);
    swap(arr[randIdx], arr[low]);

    int pivot = arr[low];
    int i = low;
    int j = high;
    while(i < j)
    {
        while(i < j && arr[j] >= pivot) --j;
        arr[i] = arr[j];
        while(i < j && arr[i] <= pivot) ++i;
        arr[j] = arr[i];
    }
    arr[i] = pivot;
    return i;
}

void quickSort(int arr[], int low, int high)
{
    if(low >= high) return;
    int pos = partition(arr, low, high);
    quickSort(arr, low, pos - 1);
    quickSort(arr, pos + 1, high);
}

void print(int arr[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        cout << arr[i] << " " << endl;
    }
}

int main(int argc, char *argv[])
{
    int arr[] = {123,54,-2,1, 43,1 , 345 ,-2, -100};
    quickSort(arr, 0, 7);
    print(arr, 8);
    return 0;
}

