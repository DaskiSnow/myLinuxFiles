#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

class LRUCache {
friend void test();
public:
    LRUCache(int capacity)
    : _capacity(capacity)
    {
        for(int i = 0; i < capacity; ++i)
        {
            _q.push_back({{-1, -1}, 0});
        }
        _q.shrink_to_fit();
        
    }



    int get(int key) 
    {
        int value = -1;
        for(auto & x : _q)
        {
            if(x.first.first == key)
            {
                x.second = -1;    // 重置计时器
                value = x.first.second;
            }
            ++x.second;     // 计时器加1
        }
        make_heap(_q.begin(), _q.end(),Com()); 
        return value;
    }

    void put(int key, int value) 
    {
        bool inner = false;
        for(auto & x : _q)
        {
            if(x.first.first == key)
            {
                inner = true;
                x.first.second = value;
                x.second = -1;
            }
            ++x.second;     // 计时器加1
        }
        if(inner == true) return;
        
        if(_capacity == _q.size())
        {
            pop_heap(_q.begin(), _q.end(),Com()); 
            cout << "被淘汰" << _q.back().first.first << endl;
            _q.pop_back();
            
        }
        _q.push_back({{key, value}, 0});
        push_heap(_q.begin(), _q.end(),Com());
        
    }
private:
    deque<pair<pair<int, int>, int>> _q;  // key-value，key值为数字，value用于计时
    size_t _capacity;
private:
    struct Com
    {
        bool operator()(const pair<pair<int, int>, int> & a, const pair<pair<int, int>, int> & b)
        {
            return a.second < b.second; // 大根堆
        }
    };
};

void test()
{
    // [[2],[2,1],[1,1],[2,3],[4,1],[1],[2]]
    size_t capacity = 2;
    LRUCache lRUCache(capacity);
    lRUCache.put(2, 1); 
    lRUCache.put(1, 2); 
    lRUCache.put(2, 3); 
    lRUCache.put(4, 1); 
    cout << lRUCache.get(1) << endl;  
    cout << lRUCache.get(2) << endl;  
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

