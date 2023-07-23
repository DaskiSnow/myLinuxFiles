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
        calcDist(*(--_wl.end()));

        if(_wl.front().second == -1) return 0;
        return _wl.front().second + 1;

    }

    void calcDist(pair<string, int> & iw)
    {
        for(auto & w : _wl)
        {
            // cout << w.first << " " << w.second << " " << ajacent(w.first, iw.first) << endl;
            if(ajacent(w.first, iw.first) && ((iw.second + 1 < w.second) || w.second == -1))
            {
              //   cout << "if " << w.first << "  " << w.second << endl;
                w.second = iw.second + 1;
                calcDist(w); // TODO
            }
        }
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
};

void test()
{
    Solution s; 
    string beginWord = "leet";
    string endWord = "code";
    vector<string> wordList = {"leet","lest","lose","lode","robe","lost","code"};
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

