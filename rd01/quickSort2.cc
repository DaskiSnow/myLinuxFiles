#include <func.hh>
#include <stdlib.h>
#include <time.h>

using namespace std;

void swap(int & a, int & b)
{
    if(a == b) return;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

int partition(int arr[], int low, int high)
{
    // 随机选取
    srand(clock());
    int randIdx = low + (rand() % (high - low + 1));
    /* printf("%d, %d\n", arr[low], arr[randIdx]); */
    swap(arr[low], arr[randIdx]);
    /* printf("%d, %d\n", arr[low], arr[randIdx]); */

    // 听说可以避免抖动现象, 但每次移动赋值操作更多
    int pivot = arr[low];
    int storeIdx = low;
    int i = low;
    while(i <= high)
    {
        if(arr[i] < pivot)
        {
            swap(arr[i], arr[storeIdx]);
            ++storeIdx;
        }
        ++i;
    }
    arr[storeIdx] = pivot;
    return storeIdx;
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
    quickSort(arr, 0, 8);
    print(arr, 9);
    return 0;
}

