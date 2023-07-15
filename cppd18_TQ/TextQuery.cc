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
private:
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

TextQuery::TextQuery(ifstream & ifs)
: _pFile(new vector<string>)
, _pStrToFreq(new map<string, int>)
, _pStrToLine(new map<string, set<int>>)
{
    if(!ifs) {
        cerr << "open file failed" << endl;
        return ;
    }

    string line;
    ssize_t num = -1; // 对应行内容vector的索引
    while(getline(ifs, line)) {
        ++num;
        // 保存内容
        (*_pFile).push_back(line);

        // 将字母全变成小写
        for(char & ch : line) {
            ch = tolower(ch);
        }

        vector<string> words = getWords(line);    
        for(string & word : words) 
        {
            ++(*_pStrToFreq)[word];  //  插入/更新频率(没有则插入，有则更新)            
            (*_pStrToLine)[word].insert(num); // 插入行号
        }
    }
    ifs.close();
}

QueryResult TextQuery::query(const string & qstr) const
{
    if((*_pStrToFreq).count(qstr) == 0)
    {
        // 单词不存在
        static set<int> nonline;
        return QueryResult(qstr, 0, nonline, _pFile);
        
    }
    else
    {
        // 存在
        return QueryResult(qstr, (*_pStrToFreq)[qstr], (*_pStrToLine)[qstr], _pFile);

    }
}

vector<string> TextQuery::getWords(const string & line)
{
    vector<string> words;
    int length = line.length();

    // 状态机取单词
    bool wordState = false;
    int wordStartIdx = 0;
    int wordEndIdx = 0;
    int i = 0;
    for(; i < length; ++i) {
        // 符号状态->字母状态
        if(!wordState && isalpha(line[i])) {
            wordStartIdx = i;
            wordState = true;
        }
        // 字母状态->符号状态, 取单词
        else if(wordState && !isalpha(line[i])){
            wordEndIdx = i - 1;
            wordState = false;

            // 取单词
            string newword = line.substr(wordStartIdx, wordEndIdx - wordStartIdx + 1);
            words.push_back(newword);
        }
    }

    // 取末尾单词（如果有）
    if(wordState) {
        wordEndIdx = i;
        string newword = line.substr(wordStartIdx, wordEndIdx - wordStartIdx + 1);
        words.push_back(newword);
    }

    return words;
}

//void test()
//{
//    ifstream ifs("The_Holy_Bible.txt");
//
//    TextQuery tq(ifs);
//    QueryResult qr = tq.query("hello");
//
//    cout << "qstr: " << qr._qstr << endl;
//    
//    cout << "freq: " << qr._freq << endl;
//    for( auto line : qr._lines)
//    {
//        cout << "hel" << endl;
//        cout << "(Line:"<<line + 1 << ")  " << (*qr._pFile)[line] << endl;;
//    }
//}
//
//void test2()
//{
//}

