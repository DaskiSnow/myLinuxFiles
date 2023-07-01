#include <iostream>
#include <stdio.h>
using namespace std;

class A {
public:
    A() {
        printf("A\n");
    }

    ~A() {
        printf("A over\n");
    }

};

class B {
public:
    B() {
        printf("B\n");
    }

    ~B() {
        printf("B over\n");
    }

};

class C {
public:
    C() {
        printf("C\n");
    }

    ~C() {
        printf("C over\n");
    }

};

class D {
public:
    D() {
        printf("D\n");
    }

    ~D() {
        printf("D over\n");
    }

};


C c;
int main()
{
    A *pa = new A();
    B b;
    static D d;
    delete pa;
    
    return 0;
}

