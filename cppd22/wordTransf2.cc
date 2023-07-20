#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <sstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::unordered_map;
using std::ifstream;
using std::vector;
using std::istringstream;
using std::ostringstream;

class Reader
{
friend void test();
friend void test2();
public:
    Reader(ifstream & srcFile, ifstream & mapFile)
    {
        getContent(srcFile);
        buildMap(mapFile); 
        for(const auto & line : _content)
        {
            istringstream iss(line);
            ostringstream oss;
            string word;
            while(iss >> word)
            {
                string replacer = transform(word);
                if(replacer.size() == 0)
                {
                    oss << word << " ";
                }
                else
                {
                    oss << replacer.substr(1) << " ";
                }
            }
            _newContent.push_back(oss.str());
        }
    }

    void print()
    {
        for(const auto & line : _newContent)
        {
            cout << line << endl;
        }
    }

private:
    void getContent(ifstream & srcFile)
    {
        string line;
        while(getline(srcFile, line))
        {
            _content.push_back(line);
        }
    }

    void buildMap(ifstream & mapFile)
    {
        string word;
        string replacer;
        while(mapFile >> word)
        {
            getline(mapFile, replacer);
            _map.insert({word, replacer});
        }
    }

    string transform(string & word)
    {
        if(_map.find(word) != _map.end())
        {
            return _map[word];
        }
        else
        {
            return "";
        }
    }


private:
    vector<string> _content;
    vector<string> _newContent;
    unordered_map<string, string> _map;
};

void test()
{
    ifstream srcFile("file1.txt");
    ifstream mapFile("map.txt");
    Reader reader(srcFile, mapFile);
    for(const auto & line : reader._content)
    {
        cout << line << endl;
    }
    cout << "_____________________" << endl;
    for(const auto & rule : reader._map)
    {
        cout << rule.first << " " << rule.second << endl;
    }
    cout << "_____________________" << endl;
    for(const auto & line : reader._newContent)
    {
        cout << line << endl;
    }
}

void run()
{
    ifstream srcFile("file1.txt");
    ifstream mapFile("map.txt");
    Reader reader(srcFile, mapFile);
    reader.print(); 
}


int main(int argc, char* argv[])
{
    run();
    return 0;
}

