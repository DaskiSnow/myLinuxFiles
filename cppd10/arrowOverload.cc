#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

struct Data
{
    int data = 100;
    void print()
    {
        cout << "Inner struct Data" << endl;
    }
};

class Layer1 
{
public:
    Layer1(int pubNum = 0, int privNum = 0)
    : _pubNum(pubNum)
    , _privNum(privNum)
    {}

    Data* operator->() {
        return &_dataStruct;
    } 

    int getPrivatedNum() const {
        return _privNum;
    }

public:
    int _pubNum;
private:
    int _privNum;
    Data _dataStruct;

};


class Layer2 
{
public:
    Layer2(Layer1 & pt)
    : _pt(pt)
    {}

    Layer1 * operator->() 
    {
        return &_pt;
    }
    
    //Layer1 & operator->()
    //{
    //    return _pt;
    //}

private:
    Layer1 & _pt;
};

int main(int argc, char* argv[])
{
    Layer1 l1(3, 4);
    Layer2 l2(l1);

    // Q1: 返回类型为指针类型？
    // cout << l2->data << endl;        // ×
    cout << l2->operator->()->data << endl; // √
    

    // Q2: 返回类型为引用类型呢？
    // cout << l2->data << endl; // √

    
    return 0;
}

