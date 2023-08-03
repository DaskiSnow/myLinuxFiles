#include "Point.hh"
#include <stdio.h>

class Point::PointImpl
{
public:
    PointImpl(int ix, int iy);
    void print();
private:
    int getX();
    int getY();
private:
    int _ix;
    int _iy;
};

Point::Point(int ix, int iy)
: _impl(new PointImpl(ix, iy))
{}

void Point::print()
{
    _impl->print();
}

Point::~Point()
{
    delete _impl;
}

Point::PointImpl::PointImpl(int ix, int iy)
: _ix(ix)
, _iy(iy)
{}

void Point::PointImpl::print()
{
    printf("(%d, %d)\n", getX(), getY());
}

int Point::PointImpl::getX()
{
    return _ix + 1;
}

int Point::PointImpl::getY()
{
    return _iy + 1;
}
