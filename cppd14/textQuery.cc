#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::ifstream;
using std::vector;
using std::map;
using std::set;
using std::string;

class TextQuery
{
public:
    void readFile(const string & filename);
    void query(const string & word);//

private:
    vector<string> dealword(const string & str); // 将一行分割成一个个单词  

private:
    vector<string> _lines;//O(1)
    map<string, set<int> > _wordLineNum;//the the
    map<string, int> _dictMap;//

};

void TextQuery::readFile(const string & filename)
{
    ifstream ifs(filename);
    if(!ifs) {
        cerr << "open file failed" << endl;
        exit(1);
    }

    string line;
    int lineNum = 0;
    while(getline(ifs, line)) {
        // 存储每一行
        _lines.push_back(line);

        // 将字母全变成小写
        for(char & ch : line) {
            ch = tolower(ch);
        }

        vector<string> words = dealword(line);    
        for(string & word : words) 
        {
            // 旧单词
            map<string, int>::iterator ret = _dictMap.find(word);
            //if(ret != _dictMap.end())  // 旧单词
            //{
            //    _dictMap[word]++;
            //}
            //else
            //{ 
            //    // 新单词
            //    _dictMap.insert({word, 1});
            //}

            ++_dictMap[word];

            // 更新_wordLineNum，记录该单词的行号
            _wordLineNum[word].insert(lineNum);

        }
        ++lineNum;
    }
    ifs.close();

}

// 功能：切割成一个个单词，并返回一个单词数组
vector<string> TextQuery::dealword(const string & str) {
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

// 查询某单词，并在标准输出打印出现次数、行号、行内容
void TextQuery::query(const string & word)
{
    int occurTimes = _dictMap[word];
    cout << "-------------------------------------" << endl;
    printf("%s occur %d times\n", word.c_str(), occurTimes);
    for(const int linenum : _wordLineNum[word])
    {
        printf("(line %-5d) %s\n", linenum + 1, _lines[linenum].c_str());
    }
    cout << "-------------------------------------" << endl;
}

//程序测试用例
//void test()
//{
//    string filename;
//    filename = "The_Holy_Bible.txt";
//
//    string queryWord("holy");
//
//    TextQuery tq;
//    tq.readFile(filename);
//    tq.query(queryWord);
//}

int main(int argc, char* argv[])
{
    TextQuery tq;
    string filename;
    string queryWord;

    cout << "Input filename: ";
    cin >> filename;
    tq.readFile(filename);

    cout << "Input a word wanted to query: ";
    cin >> queryWord;
    tq.query(queryWord);

    return 0;
}

