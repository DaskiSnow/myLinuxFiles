#include <iostream>
#if defined( _MSC_VER )
	#if !defined( _CRT_SECURE_NO_WARNINGS )
		#define _CRT_SECURE_NO_WARNINGS		// This test file is not intended to be secure.
	#endif
#endif

#include "tinyxml2.h"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <vector>
using std::vector;

#if defined( _MSC_VER ) || defined (WIN32)
	#include <crtdbg.h>
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	_CrtMemState startMemState;
	_CrtMemState endMemState;
#else
	#include <sys/stat.h>
	#include <sys/types.h>
#endif

#include <cstdlib>
#include <regex>
using namespace tinyxml2;
using namespace std;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
    friend void test2();
public:
    void parseRes(const string & filename); // 解析
    void dump(const string & filename); // 输出
private:
    string dealString(const string & s); // 处理标签
    
private:
    vector<RssItem> _res;

};

// 解析
void RssReader::parseRes(const string & filename)
{
    XMLDocument doc;
    doc.LoadFile(filename.c_str());

    // 遍历兄弟结点
    XMLElement* itemNode = doc.FirstChildElement()->FirstChildElement( "channel" )->FirstChildElement( "item" ); 
    while(itemNode != nullptr)
    {
        XMLElement* titleNode = itemNode->FirstChildElement( "title" );
        XMLElement* linkNode = itemNode->FirstChildElement( "link" );
        XMLElement* descriptionNode = itemNode->FirstChildElement( "description" );
        XMLElement* contentNode = itemNode->FirstChildElement( "content:encoded" );

        RssItem ri = {titleNode->GetText(), linkNode->GetText(), descriptionNode->GetText(), contentNode->GetText()};
        _res.push_back(ri);
        itemNode = itemNode->NextSiblingElement();//下一个兄弟节点
    }

    // 除去标签
    for(auto & ri : _res)
    {
        ri.description = dealString(ri.description);
        ri.content = dealString(ri.content);
    }
} 

// 输出
void RssReader::dump(const string & filename) 
{
    XMLDocument doc;

    int docid = 0;
    for(const auto & ri : _res)
    {
        ++docid;
        // 创建docNode
        XMLElement* docNode = doc.NewElement("doc");
        
        // docid
        XMLElement* docidNode = doc.NewElement("docid");
        XMLText* docidText = doc.NewText(std::to_string(docid).c_str());
        docidNode->InsertEndChild(docidText);
        docNode->InsertEndChild(docidNode);

        // title
        XMLElement* titleNode = doc.NewElement("title");
        XMLText* titleText = doc.NewText(ri.content.c_str());
        titleNode->InsertEndChild(titleText);
        docNode->InsertEndChild(titleNode);

        // link
        XMLElement* linkNode = doc.NewElement("link");
        XMLText* linkText = doc.NewText(ri.link.c_str());
        linkNode->InsertEndChild(linkText);
        docNode->InsertEndChild(linkNode);
    
        // description
        XMLElement* descriptionNode = doc.NewElement("description");
        XMLText* descriptionText = doc.NewText(ri.description.c_str());
        descriptionNode->InsertEndChild(descriptionText);
        docNode->InsertEndChild(descriptionNode);
        
        // content
        XMLElement* contentNode = doc.NewElement("content");
        XMLText* contentText = doc.NewText(ri.content.c_str());
        contentNode->InsertEndChild(contentText);
        docNode->InsertEndChild(contentNode);

        // 插入docNode
        doc.InsertEndChild(docNode);
    }
    doc.SaveFile(filename.c_str());
}

// 去除标签
string RssReader::dealString(const string & s)
{
    std::regex reg("<[^<>]*>");
    std::string replacement = "";
    std::string new_str = std::regex_replace(s, reg, replacement);
    return new_str;
}

void test()
{
    string srcPath;
    string dumpPath;
    cout << "input srcPath:";
    cin >> srcPath;
    cout << "input dumpPath:";
    cin >> dumpPath;

    RssReader rr;
    rr.parseRes(srcPath);
    rr.dump(dumpPath);
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

