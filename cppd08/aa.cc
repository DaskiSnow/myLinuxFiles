#include <iostream>
#include <string>
#include <limits>
using std::cout;
using std::cin;
using std::endl;
using std::string;

// 输入输出流练习
// 总结：
// ① EOF:failbit|eofbit  能获取到正常的子集（整数/小数/字符串）:goodbit  其他: failbit
// ② cin属于全缓冲和行缓冲
// ③ 首次cin失败会置将变量0(除了EOF)，而连带失败的cin不会将变量置0
// ④ 失败后，返回false，且剩余字符还在输入缓冲区，继续正常cin需要clear()+ignore();
void test1() {
    double num = 1.1;
    cin >> num; 
    cout << "cin.bad() = " <<cin.bad() << endl;
    cout << "cin.fail() = " <<cin.fail() << endl;
    cout << "cin.eof() = " <<cin.eof() << endl;
    cout << "cin.good() = " <<cin.good() << endl;
    cout << num << endl;
    double num2 = 2.2;
    cin >> num2; 
    cout << "---------------" << endl;
    cout << "cin.bad() = " <<cin.bad() << endl;
    cout << "cin.fail() = " <<cin.fail() << endl;
    cout << "cin.eof() = " <<cin.eof() << endl;
    cout << "cin.good() = " <<cin.good() << endl;
    cout << num2 << endl;
    cin.clear();
    string num3 = "ccc";
    cin >> num3; 
    cout << "cin.bad() = " <<cin.bad() << endl;
    cout << "cin.fail() = " <<cin.fail() << endl;
    cout << "cin.eof() = " <<cin.eof() << endl;
    cout << "cin.good() = " <<cin.good() << endl;
    cout << num3 << endl;
    cout << "---------------" << endl;
}

// 标准输入流的返回值测试
// 总结：只要没goodbit，返回值为false
void test2() {
    double num;
    while(1){
        if(cin >> num) {
            cout << "true" << endl;
        }
        else {
            cout << "false" << endl;
        }

    }
}

// 标准输出流的字符串输出测试
#include <typeinfo>
void test3() {
    const char* str = "abc";
    const int a = 1;
    const int * b = &a;
    char str2[10] = "def";

    cout << a << b << str << str2 << endl;
    
}

// 健壮性读取
void test() {
    string str;
    while(cin >> str, cin.eof()) {
        if(cin.bad()) {
            cout << "bad" << endl;
        }
        else if(cin.fail()) {
            cout << "fail" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            cout << str << endl;
        }
    }
}

// 文件流测试
#include <fstream>
using std::ifstream;
void test4() {
    ifstream ifs;
    ifs.open("a.cc");
    if(!ifs.good()) {
        cout << "ifs is no good" << endl;
    }
    string word;
    while(ifs >> word) {
        cout << word << endl;
    }
    if(ifs.good()) {
        cout << "good" << endl;
    }
    else if(ifs.eof()) {
        cout << "eod" << endl;
    }
    else if(ifs.bad()) {
        cout << "bad" << endl;
    } 
    else if(ifs.fail()) {
        cout << "fail" << endl;
    } 
    ifs.close();
}

int main2(int argc, char* argv[])
{
    test4();
    return 0;
}

int main() {
    test4();
}

