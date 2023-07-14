#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

struct test1 {
    char a[5];
    int aa;
    double aaa;
    char aaaa;

    struct test2 {
        char b;
        double bb;
        int bbb;
        
    };  

    char aaaaa[1];
    int aaaaaa;    
};  //64？

int main()
{
    test1 a;
    printf("%d\n", sizeof(a));
}
