#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

const double PAI = 3.1415926;

class Circle 
{
public:
    Circle()
    : _radius(0)
    {}

    Circle(double r)
    : _radius(r)
    {}

    double getArea()
    {
        return PAI * _radius * _radius; 
    }

    double getPerimeter()
    {
        return 2.0 * PAI * _radius;
    }

    void show()
    {
        cout << "r = " << _radius << endl
            << "Perimeter = " << getPerimeter() << endl
            << "Area = " << getArea() << endl;
    }

private:
    double _radius;
};


class Cylinder
: public Circle
{
public:
    Cylinder(double r, double h)
    : Circle(r)
    , _h(h)
    {}

    double getVolume()
    {
        return getArea() * _h;
    }

    void showVolume()
    {
        cout << "Volume = " << getVolume() << endl;
    }

private:
    double _h;
};

int main(int argc, char* argv[])
{
    Cylinder cylinder(5, 2.5);
    cylinder.Circle::show();
    cylinder.showVolume();
    return 0;
}

