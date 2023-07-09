#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::istream;

// 实现一个采用COW技术的自定义字符串类型CowString，
// 并让其下标访问运算符能区分出读操作和写操作
// 方案：重载赋值运算符，为了避免与原生的赋值运算符函数冲突(char = char)，
// 将左操作数用一个自定义类封装，即[]的返回值应为一个自定义类型, 因此要重载<<和>>
// 存储结构：Size(4B) Capacity(4B) Refcount(4B) Value(*)

class CowString 
{
class Data;
public:
    friend void test();
    CowString();
    CowString(const char *);
    CowString(const CowString &);
    CowString & operator=(const char *);
    CowString & operator=(const CowString &);
    Data operator[](int);   // 返回的是一个临时对象, 故返回类型为类类型
    friend ostream & operator<<(ostream & os, const CowString & cs);  // 对CowString的读操作
    friend istream & operator>>(istream & os, CowString & cs);        // 对CowString的写操作, 写时赋值
    friend ostream & operator<<(ostream & os, const Data data); // 对Data._ch值的读操作
    friend istream & operator>>(istream & os, Data data);       // 间接对CowString某字符的写操作, 写时赋值
    ~CowString();
private:
    // Inner Class
    class Data {
    public:
        Data(CowString & cs, char retCh, int idx)
        : _cs(cs)
        , _ch(retCh)
        , _idx(idx)
        {}

        Data operator=(char ch); // 写时复制
        Data operator=(const Data data); // 写时复制
        friend ostream & operator<<(ostream & os, const Data data); // 两次声明友元函数，是为了能同时访问CowString和Data的私有成员
        friend istream & operator>>(istream & os, Data data);       // 同上

    private:
        CowString & _cs;
        char _ch;    // 存储下标返回运算的字符值
        int _idx;    // 存储下标
    };

private:
    void initSCR(int, int, int); // 初始化Size, Capacity, Refcount
    void release(); // 释放左操作数
    void incRef();
    void decRef();
    int getSize();
    int getCapacity();
    int getRef();

private:
    char * _point;
};

void CowString::initSCR(int initSize, int initCapacity, int initRefcount)
{
    *(int *)(_point - 12) = initSize;       // Size
    *(int *)(_point - 8) = initCapacity;    // Capacity
    *(int *)(_point - 4) = initRefcount;    // Refcount
}

void CowString::release()
{
    if(getRef() <= 1)
    {
        delete [] (_point - 12);
        _point = nullptr;
    }
    else
    {
        decRef();
    }
}

void CowString::incRef()
{
    ++*(int *)(_point - 4);
}

void CowString::decRef()
{
    --*(int *)(_point - 4);
}

int CowString::getSize()
{
    return *(int *)(_point - 12);
}

int CowString::getCapacity()
{
    return *(int *)(_point - 8);
}

int CowString::getRef()
{
    return *(int *)(_point - 4);
}

CowString::CowString()
{
    _point = new char[12 + 1]() + 12;
    initSCR(1, 1, 1);
}

CowString::CowString(const char * cstr)
{
    if(cstr == nullptr) 
    {
        _point = new char[12 + 1]() + 12;
        initSCR(1, 1, 1);
        return;
    }
    int len = strlen(cstr);
    _point = new char[12 + len + 1]() + 12;
    initSCR(len + 1, len + 1, 1);
    strcpy(_point, cstr);
}

// 浅拷贝
CowString::CowString(const CowString & cs)
    : _point(cs._point)
{
    incRef();
}


CowString & CowString::operator=(const char * cstr) 
{
    // 1. 判断内容是否一样
    if(cstr != nullptr && strcmp(_point, cstr) == 0) return *this;

    // 2. 释放左操作数
    release();

    // 3. 深拷贝(C风格字符串，必须开辟新堆空间)
    if(cstr == nullptr)
    {
        _point = new char[12 + 1]() + 12;
        initSCR(1, 1, 1);
    }
    else
    {
        int len = strlen(cstr);
        _point = new char[12 + len + 1]() + 12;
        initSCR(len, len, 1);
        strcpy(_point, cstr);
    }

    // 4. 返回*this
    return *this;
}

CowString & CowString::operator=(const CowString & cs)
{
    // 1. 判断自赋值
    if(this == &cs) return *this;

    // 2. 释放左操作数
    release();

    // 3. 浅拷贝
    _point = cs._point;
    incRef();

    // 4. 返回*this
    return *this; 

}

CowString::Data CowString::operator[](int idx)
{
    // 下标值非法
    if(idx < 0 || idx >= getSize())
    {
        static char nullchar = '\0';
        Data data(*this, nullchar, -1);
        return data;
    }

    // 下标合法
    Data data(*this, _point[idx], idx);        
    return data;
}

// 重载内部类的赋值运算符函数，修改一个字符(写时复制)
CowString::Data CowString::Data::operator=(char ch)
{
    // 开辟新空间，将堆空间信息拷贝
    char * newPoint = new char[12 + _cs.getSize() + 1]() + 12;
    *(int *)(newPoint - 12) = _cs.getSize();
    *(int *)(newPoint - 8) = _cs.getCapacity();
    *(int *)(newPoint - 4) = 1;
    strcpy(newPoint, _cs._point);

    // 释放左操作数
    _cs.release();

    // 指向新的堆空间
    _cs._point = newPoint;

    // 执行某字符的写操作
    _cs._point[_idx] = ch;

    Data retData(_cs, ch, _idx);

    return retData; // 连续=
}

// 修改一个字符(写时复制)  cs1[n] = cs2[m]
CowString::Data CowString::Data::operator=(const Data data)
{
    // 同理，开辟新空间后拷贝
    char * newPoint = new char[12 + _cs.getSize() + 1]() + 12; 
    *(int *)(newPoint - 12) = _cs.getSize();
    *(int *)(newPoint - 8) = _cs.getCapacity();
    *(int *)(newPoint - 4) = 1;
    strcpy(newPoint, _cs._point);

    // 同理, 释放左操作数
    _cs.release();

    // 同理, 指向新的堆空间
    _cs._point = newPoint;

    // 同理, 执行某字符的写操作
    _cs._point[_idx] = data._ch;

    Data retData(_cs, _ch, _idx);

    return retData; // 连续=
}

// 对CowString的读操作
ostream & operator<<(ostream & os, const CowString & cs)  
{
    os << cs._point;
    return os;
}

// 对CowString的写操作, 写时赋值
istream & operator>>(istream & is, CowString & cs)        
{
    // 从标准输入中读取一行数据到buf中
    char buf[2048] = {0};
    read(STDIN_FILENO, buf, sizeof(buf) - 1);
    buf[strlen(buf) - 1] = '\0'; // 剔除末尾的换行符

    // 释放原CowString
    cs.release();

    // 深拷贝(开辟新堆空间)
    int len = strlen(buf);
    cs._point = new char[12 + len + 1]() + 12;
    cs.initSCR(len, len, 1);
    strcpy(cs._point, buf);

    // 返回is
    return is;
}

// 对Data._ch值的读操作
ostream & operator<<(ostream & os, const CowString::Data data) 
{
    os << data._ch;
    return os;
}

// 间接对CowString某字符的写操作, 写时赋值
istream & operator>>(istream & is, CowString::Data data)      
{
    // 用户指定的idx非法, 不执行写操作, 仅接收一个无用字符 
    if(data._idx == -1) 
    {
        int trashCh;
        is >> trashCh;
        return is;
    }

    // 申请新堆空间，拷贝数据并执行字符的写操作
    int len = data._cs.getSize();
    char * newPoint = new char[12 + len + 1]() + 12;
    strcpy(newPoint, data._cs._point);
    cin >> newPoint[data._idx];
    
    // 释放原CowString
    data._cs.release();

    // 深拷贝(指向新的堆空间)
    data._cs._point = newPoint;
    
    return is;    
}

CowString::~CowString()
{
    if(_point == nullptr) return; 
    if(getRef() <= 1) 
    {
        delete [] (_point - 12);
        return;
    }
    decRef();
}

void test2()
{
    char ch1, ch2;
    cin >> ch1 >> ch2;
    cout << ch1 << endl;
    cout << ch2 << endl;
}

void test()
{
    // 构造函数、<<测试
    CowString temp("WOW");
    CowString temp2("QAQ");
    CowString cs1;
    CowString cs2 = "CCSS2";
    CowString cs3 = temp;
    cout << "cs1=" << cs1 <<endl;
    cout << "cs2=" << cs2 << endl;
    cout << "cs3=" << cs3 << endl;

    // 赋值运算符=测试，地址和引用的验证
    cout << "----------------------" << endl;
    cs3 = "CS3";
    cout << "cs3=" << cs3 << endl;
    printf("Before cs3 Addr=%p\n", cs3._point);
    cs3 = temp;
    cout << "cs3=" << cs3 << endl;
    printf("After cs3  Addr=%p\n", cs3._point);
    printf("      temp Addr=%p\n", temp._point);
    cout << "cs3  RefCount=" << cs3.getRef() << endl;
    cout << "temp RefCount=" << cs3.getRef() << endl;

    // 下标运算符[]通过<< 的读测试
    cout << "----------------------" << endl;
    CowString cs4 = "CS4";
    printf("Before cs4 Addr=%p\n", cs4._point);
    cout << cs4[0] << " " << cs4[1] << " " << cs4[2] << endl;
    printf("After cs4  Addr=%p\n", cs4._point);

    // 下标运算符[]通过=、>>的 写测试
    cout << "----------------------" << endl;
    CowString cs5 = "CS5";
    CowString cs5_backup = cs5;   // 不加这一句，验证时会Befor和After的地址相同(旧地址被释放后再被申请)
    cout << "cs5=" << cs5 << endl;
    printf("Before'=' cs5 Addr=%p\n", cs5._point);
    cs5[0] = 'c';
    cs5[1] = 's';
    cout << "cs5=" << cs5 << endl;
    printf("After'='  cs5 Addr=%p\n", cs5._point);
    cs5_backup = cs5;   // 不加这一句，验证时会Befor和After的地址相同(旧地址被释放后再被申请)
    cout << "输入两个字符修改cs5[0]和cs5[1]" << endl; 
    cin >> cs5[0] >> cs5[1];
    printf("After'>>' cs5="); cout << cs5 << endl;
    printf("After'>>' cs5 Addr=%p\n", cs5._point);

    // 其他情况
    cout << "----------------------" << endl;
    CowString spcCS = nullptr;
    cout << spcCS << endl;
    cout << spcCS[-1000] << endl;
    spcCS[-1000] = 'B';
    cout << spcCS << endl;
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

