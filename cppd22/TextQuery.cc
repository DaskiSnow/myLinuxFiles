#include "TextQuery.hh"

void QueryResult::print()
{
   cout << "Executing Query for: " << _qstr << endl; 
   cout << _qstr << " occurs " << _freq << (_freq > 1 ? " times" : " time") << endl;
   for(const auto & lineIdx : _lines)
   {
       printf("(line %d) %s\n", lineIdx + 1, (*_pFile)[lineIdx].c_str());
   }
}

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

void test()
{
    ifstream ifs("The_Holy_Bible.txt");

    TextQuery tq(ifs);
    auto start_time = std::chrono::high_resolution_clock::now();
    time_t start = time(NULL);
    QueryResult qr = tq.query("good");
    time_t end = time(NULL);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
    double time_in_seconds = duration.count();
    cout << "cost time = " << time_in_seconds << endl;

    cout << "qstr: " << qr._qstr << endl;
    
    cout << "freq: " << qr._freq << endl;
    for( auto line : qr._lines)
    {
        cout << "hel" << endl;
        cout << "(Line:"<<line + 1 << ")  " << (*qr._pFile)[line] << endl;;
    }
}

int main()
{
    test();
    return 0;
}
