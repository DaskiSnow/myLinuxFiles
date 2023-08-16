#include <func.hh>

using namespace std;

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low;
    int j = high;
    while(i < j)
    {
        if(i < j && arr[j] >= pivot) --j;
        arr[i] = arr[j];
        if(i < j && arr[i] <= pivot) ++i;
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
    int arr[] = {123,35,46654,1,-1,0,0,12};
    quickSort(arr, 0, 7);
    print(arr, 8);
    return 0;
}

