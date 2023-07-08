// 6_Line.hh
class Line {
public:
    Line(int, int, int, int);
    ~Line();
    void printLine();
private:
    class LineImpl;
    LineImpl * lineimpl;
};

