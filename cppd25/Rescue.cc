#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
using namespace std;

class Solution
{
friend void test();
public:
    Solution(int row, int col)
    : _row(row)
    , _col(col)
    , _res(-1)
    , _matrix(row, vector<pair<char, int>>(col, {'\0', 0}))
    {}

    void readMap()
    {
        for(int i = 0; i < _row; ++i)
        {
            for(int j = 0; j < _col; ++j)
            {
                cin >> _matrix[i][j].first;
                if(_matrix[i][j].first == 'a')
                {
                    _ax = i;
                    _ay = j;
                }
                else if(_matrix[i][j].first == 'r')
                {
                    _rx = i;
                    _ry = j;
                }
            }
        }
    }

    int calc()
    {
        _q.push({_rx, _ry, 0});
        while(!_q.empty())
        {
            auto p = _q.top();
            int x = p.x;
            int y = p.y;
            int t = p.t;
            _q.pop();
            
            /* cout << p.x << " " << p.y << " " << p.t << endl; */
            
            // 找到其中一条路径
            if(_matrix[x][y].first == 'a' && (t < _res || _res == -1) )
            {
                _res = t;
            }

            if(x - 1 >= 0 && _matrix[x - 1][y].first != '#')
            {
                calc_aux(x - 1, y, t);
            }
            if((x + 1 < _row) && _matrix[x + 1][y].first != '#')
            {
                calc_aux(x + 1, y, t);
            }
            if(y - 1 >= 0 && _matrix[x][y - 1].first != '#')
            {
                calc_aux(x, y - 1, t);
            }
            if(y + 1 < _col && _matrix[x][y + 1].first != '#')
            {
                calc_aux(x, y + 1, t);
            }
        }
        return _res;
    }

private:
    struct pos
    {
        int x;
        int y;
        int t;
    };

    // 小根堆
    struct Less
    {
        bool operator()(const pos & a, const pos & b) const
        {
            return a.t > b.t;
        }
    };

    void calc_aux(int nx, int ny, int t)
    {
        if(_matrix[nx][ny].second == 0)
        {
            auto ch = _matrix[nx][ny].first;
            if(ch == 'x') 
            {
                _q.push({nx, ny, t + 2});   
            }
            else
            {
                _q.push({nx, ny, t + 1});   
            }
        }
        _matrix[nx][ny].second = 1;
    }

private:
    int _row;
    int _col;
    int _res; // 最短时间
    vector<vector<pair<char, int>>> _matrix; // char表示坐标的字符, int表示该路径是否被走过(0-未走过 1-走过)
    priority_queue<pos, std::vector<pos>, Less> _q;
    // 记录公主和骑士的坐标 
    int _ax;
    int _ay;
    int _rx;
    int _ry;
};

void test()
{
    int row, col;
    while(cin >> row >> col)
    {
        Solution s(row, col);
        s.readMap();
        int res = s.calc();
        if(res == -1)
        {
            cout << "Poor ANGEL has to stay in the prison all his life." << endl;
        }
        else
        {
            cout << s.calc() << endl;
        }
    }
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

