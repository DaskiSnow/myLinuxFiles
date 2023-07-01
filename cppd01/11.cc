#include <iostream>
#include <stdio.h>
using namespace std;

class Basic{
public:
    void print() {
        cout << "Basic" << endl;
    }
};

class Derived : public Basic {
public:
    void print() {
        cout << "Derived" << endl;
    }
};

int main()
{
    //int a[5]={1,2,3,4,5};
    //int *ptr=(int *)(&a+1);
    //printf("%d,%d",*(a+1),*(ptr-1));
    
    //int a[5] = {1,2,3,4,5};
    //int *ptr = (int *)&a; // "&a"的类型是"int (*)[5]"
    //printf("%d\n", *ptr);
    
    //const int* p = new int(10);
    //*const_cast<int*>(p) = 5;
    //cout << *p << endl;
    
   // int a = 48;
   // char b = static_cast<char>(a);
   // cout << b << endl;
   
    Basic* p = new Basic();
    Derived* p2 = dynamic_cast<Derived*>(p);
    p2->print();
}
