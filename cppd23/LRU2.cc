#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <algorithm>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
friend void test();
public:
    LRUCache(int capacity)
    : _capacity(capacity)
    {}

    int get(int key) 
    {
        auto it = _map.find(key);
        if(it == _map.end())
        {
            return -1;
        }
        int value = _map[key]->second;
        _lst.erase(_map[key]);  // 删除链的对应记录
        _map.erase(key);        // 删除_map的对应记录
        _lst.push_back({key, value});       // 重新插入到链尾
        _map.insert({key, --_lst.end()});   // _map记录其迭代器
        return value;
    }

    void put(int key, int value) 
    {
        auto it = _map.find(key);
        if(it != _map.end())
        {
            _lst.erase(it->second);     // 删除链记录
            _map.erase(key);            // 删除_map记录

            _lst.push_back({key, value});
            _map.insert({key, --_lst.end()});

            return;
        }

        if(_lst.size() == _capacity)
        {
            _map.erase(_lst.begin()->first); // 删除_map记录
            _lst.pop_front();                // 删除链头
        }
        _lst.push_back({key, value});
        _map.insert({key, --_lst.end()});
        //cout << "-----------------" << endl;
        //for(auto x : _lst)
        //{
        //    cout << x.first << " " << x.second << endl;
        //}
    }
private:
    list<pair<int, int>> _lst;  
    unordered_map<int, list<pair<int, int>>::iterator> _map;
    size_t _capacity;
};

void test()
{
    // [[2],[2,1],[2,2],[2],[1,1],[4,1],[2]]
    size_t capacity = 2;
    LRUCache lRUCache(capacity);
    lRUCache.put(2, 1); 
    lRUCache.put(2, 2); 
    cout << "-- " << lRUCache.get(2) << endl;  
    lRUCache.put(1, 1); 
    lRUCache.put(4, 1); 
    cout << "-- " << lRUCache.get(2) << endl;  
    cout << "-----------------" << endl;
    for(auto x : lRUCache._lst)
    {
        cout << x.first << " " << x.second << endl;
    }
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

