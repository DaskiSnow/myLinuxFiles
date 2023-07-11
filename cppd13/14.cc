#include <iostream>
#include <string>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Person
{
public:
    Person(const char * name, int age)
    : _age(age)
    {
        _name = new char[strlen(name) + 1]();
        strcpy(_name, name);
    }
    void display()
    {
        cout << "name = " << _name << endl 
             <<"age = " << _age << endl;
    }

private:
    int _age;
    char * _name;
};

class Emplyee
: public Person
{
public:
    Emplyee(const char * name, int age, const char * department, double salary)
    : Person(name, age)
    , _salary(salary)
    {
        _department = new char[strlen(department) + 1]();
        strcpy(_department, department);
        _totalNum++;
        _totalSalary += salary;
    }

    void display()
    {
        Person::display();
        cout << "department = " << _department << endl
             << "salary = " << _salary << endl;
    }

    static double calcAvgSalary()
    {
        return _totalSalary / _totalNum;
    }

private:
    double _salary;
    char * _department;
    static int _totalNum;
    static double _totalSalary;
};

double Emplyee::_totalSalary = 0.0;
int Emplyee::_totalNum = 0;

int main(int argc, char* argv[])
{
    Emplyee workerA("Wang", 25, "Personnel", 6000);
    Emplyee workerB("Chen", 30, "Personnel", 10000);
    Emplyee workerC("Zhang", 23, "Business", 12000);
    workerA.display();
    cout << "----------------" << endl;
    workerB.display();
    cout << "----------------" << endl;
    workerC.display();
    cout << "----------------" << endl;
    cout << "SalaryAverage = " << Emplyee::calcAvgSalary() << endl;
    return 0;
}

