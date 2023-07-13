#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <map>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::sort;
using std::map;


string dealword(const string & word);
struct Record
{
    string _word;
    int _frequency;
};

class Dictionary
{
public:
    void read(const string &filename);
    void store(const string &filename);
private:
    map<string, int> _dictMap;
    // vector<Record> _dict;
    vector<string> dealword(const string & word);
    static bool cmp(Record & a, Record & b); // 也可以重载<符号
    friend void test();
};

// 功能：切割成一个个单词，并返回一个单词数组
vector<string> Dictionary::dealword(const string & str) {
    vector<string> words;
    int length = str.length();
    
    // 状态机取单词
    bool wordState = false;
    int wordStartIdx = 0;
    int wordEndIdx = 0;
    int i = 0;
    for(; i < length; ++i) {
        // 符号状态->字母状态
        if(!wordState && isalpha(str[i])) { 
            wordStartIdx = i;
            wordState = true;
        }
        // 字母状态->符号状态, 取单词
        else if(wordState && !isalpha(str[i])){
            wordEndIdx = i - 1;
            wordState = false;

            // 取单词
            string newword = str.substr(wordStartIdx, wordEndIdx - wordStartIdx + 1);
            words.push_back(newword);
        }
    }

    // 取末尾单词（如果有）
    if(wordState) {
        wordEndIdx = i;
        string newword = str.substr(wordStartIdx, wordEndIdx - wordStartIdx + 1);
        words.push_back(newword);
    }

    return words;
}

void Dictionary::read(const string &filename) {
    ifstream ifs(filename);
    if(!ifs) {
        cerr << "open file failed" << endl;
        return ;
    }

    string line;
    while(getline(ifs, line)) {
        // 将字母全变成小写
        for(char & ch : line) {
            ch = tolower(ch);
        }

        vector<string> words = dealword(line);    
        for(string & word : words) 
        {
            // 旧单词
            //map<string, int>::iterator ret = _dictMap.find(word);
            //if(ret != _dictMap.end())  // 旧单词
            //{
            //    ++_dictMap[word];
            //}
            //else
            //{ 
            //    // 新单词
            //    _dictMap.insert({word, 1});
            //}
            
            ++_dictMap[word];  //  没有则插入，有则更新            
        }
    }
    ifs.close();
}

void Dictionary::store(const string &filename) {
    ofstream ofs(filename);

    // 写入表头
    char titlebuf[128] = {0};
    sprintf(titlebuf, "%-15s\t%s", "Word", "Frequency");
    ofs << titlebuf << endl;
    ofs << "----------------------------" << endl;

    // 写入词频统计结果
    for(auto & rec : _dictMap) {
        char linebuf[128] = {0};
        sprintf(linebuf, "%-15s\t%4d", rec.first.c_str(), rec.second);
        ofs << linebuf << endl;
    }

    ofs.close();

}

void test() {
    Dictionary dic;
    dic.read("The_Holy_Bible.txt");
    dic.store("Res.txt");
}


void test2()
{
    map<string, int>testMap;
    testMap.insert({"wo", 1});
    map<string, int>::iterator ret = testMap.find("wo");
    if(ret != testMap.end())
    {
        cout << "找到了" << endl;
        testMap["wo"]++;
    }
    else
    {
        cout << "没找到" << endl;
    }

    for(const auto it : testMap)
    {
        cout << it.first << " " << it.second << endl;
    }
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

