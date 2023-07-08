#include <iostream>
#include <limits>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

void test() {
    int num;                                                                   
    // 健壮性读取                                                              }
    while(1) { // 逗号表达式                                          
        cin >> num;
        if(cin.bad()) {                 
            cerr << "Bad stream" << endl;
        }                                                                          
        if(cin.fail()) {                                                           
            cin.clear(); // 重置流(重置状态位)                                     
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');         
            cout << "pls input int data" << endl;                                  
        }                                                                          
        if(cin.eof()) {
            cout << "eof" << endl;
        }
        else {                                                                     
            cout << "num = " << num << endl;                                       
        }                                                                          
    }                                                                              
}

int main() {
    test();
}

