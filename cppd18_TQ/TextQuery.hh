#ifndef __TextQuery_H__
#define __TextQuery_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::ifstream;
using std::vector;
using std::set;
using std::map;
using std::shared_ptr;

class QueryResult
{
friend void test();
public:
    QueryResult(const string & qstr,
                size_t freq,
                set<int> & lines,
                shared_ptr<vector<string>> pFile
                )
    : _qstr(qstr)
    , _freq(freq)
    , _lines(lines)
    , _pFile(pFile)
    {}

    void print();
public:
    string _qstr;                                   // 查询单词
    ssize_t _freq;                                  // 词频
    set<int> _lines;                                // 出现的行号集合
    shared_ptr<vector<string>> _pFile;              // 保存输入流内容
};

class TextQuery
{
    friend void test();
public:
    // 读取输入流, 并保存内容、计算词频、计算行号
    TextQuery(ifstream & ifs);  

    // 输入单词, 返回统计结果
    QueryResult query(const string & qstr) const;

private:
    // 将输入的string分割成多个"合法"的单词, 保存为vector
    vector<string> getWords(const string & line);
private:
    shared_ptr<vector<string>> _pFile;              // 保存输入流内容
    shared_ptr<map<string, int>> _pStrToFreq;       // 单词-词频
    shared_ptr<map<string, set<int>>> _pStrToLine;  // 单词-出现的行号集合
};


#endif
