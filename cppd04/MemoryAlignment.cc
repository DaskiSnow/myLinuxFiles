#include <iostream>

struct SS
{
    struct FF
    {
        double ww2; 
        int a1;
        short c1;
        char b1;
        char d1;
    }MyStructFF;
    int a;
    short c;
    char b;
    char e;
    int d;
#if 1
    double ww;
#endif
}MyStructSS;

int main()
{
    std::cout << "sizeof(SS) = " << sizeof(SS) << std::endl;
    return 0;
}

