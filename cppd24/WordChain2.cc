#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
using namespace std;

class Solution {
friend void test();
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) 
    {
        // 检查wordList是否存在endWord
        bool hasEndWord = false;
        for(const auto & str : wordList)
        {
            if(str == endWord)
            {
                hasEndWord = true;
            }
        }
        if(hasEndWord == false) return 0;
        _beginWord = beginWord;

        // 第一个元素beginWord，最后一个元素为endWord，中间为其他元素
        _wl.reserve(wordList.size() + 2);
        _wl.push_back({beginWord,-1});
        for(const auto & x : wordList)
        {
            if(x == endWord) continue;
            _wl.push_back({x, -1});
        }
        _wl.push_back({endWord, 0});
        
        // 计算距离
        int dist = calcDist();

        if(dist == -1) return 0;
        return dist + 1;

    }

    int calcDist()
    {
        // 广度优先
        _q.push_back(_wl.size() - 1);
        while(!_q.empty())
        {
            int idx = _q.front();
            _q.pop_front();
            size_t size = _wl.size();
            for(unsigned int i = 0; i < size - 1; ++i)
            {
                if(ajacent(_wl[idx].first, _wl[i].first) && 
                   ((_wl[idx].second + 1 < _wl[i].second) || _wl[i].second == -1))
                {
                    _wl[i].second = _wl[idx].second + 1;
                    _q.push_back(i);
                    if(_wl[i].first == _beginWord) return _wl[i].second;
                }
            }
        }
        return -1;
    }

    bool ajacent(const string & str1, const string & str2)
    {
        int diffNum = 0;
        for(unsigned int i = 0; i < str1.size(); ++i)
        {
            if(str1[i] != str2[i])
            {
                ++diffNum;
                if(diffNum > 1) return false;
            }
        }
        if(diffNum == 0) return false;
        return true; // diffNum = 1
    }
private:
    vector<pair<string, int>> _wl;   // int 表示到达endWord要经过的结点数
    deque<int> _q;
    string _beginWord;
};

void test()
{
    Solution s; 
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    int dist = s.ladderLength(beginWord, endWord, wordList);
    cout << dist << endl;
    //for(const auto & x : s._wl)
    //{
    //    cout << x.first << "  " << x.second << endl;
    //}

}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

