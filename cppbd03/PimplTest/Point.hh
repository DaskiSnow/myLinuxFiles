class Point
{
class PointImpl;
public:
    Point(int ix, int iy);
    ~Point();
    void print();
private:
    PointImpl * _impl;
};
