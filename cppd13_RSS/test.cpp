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

using namespace tinyxml2;
using namespace std;
int gPass = 0;
int gFail = 0;

int example_1()
{
    XMLDocument doc;
    doc.LoadFile( "resources/dream.xml" );
 
    return doc.ErrorID();
}
int example_3()
{
    static const char* xml =
        "<?xml version=\"1.0\"?>"
        "<!DOCTYPE PLAY SYSTEM \"play.dtd\">"
        "<PLAY>"
        "<TITLE>A Midsummer Night's Dream</TITLE>"
        "<TITLE2>"
        "<a>hahahahah</a>"
        "</TITLE2>"
        "</PLAY>";

    XMLDocument doc;
    // doc.LoadFile( "resources/dream.xml" );
    doc.Parse( xml );

    XMLElement* titleElement = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE2" )->FirstChildElement( "a" );
    const char* title = titleElement->GetText();
    printf( "Name of play (1): %s\n", title );
}

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
    friend void example_4();
public:
    RssReader ();
    void parseRes(); // 解析
    void dump(const string & filename); // 输出
private:
    vector<RssItem> _res;

};

RssReader::RssReader()
{

}

// 解析
void RssReader::parseRes()
{

} 

// 输出
void RssReader::dump(const string & filename) 
{

}

string dealContent(string & content)
{
    
}

void example_4()
{
    RssReader reader;
    XMLDocument doc;
    doc.LoadFile("resources/RSS.xml");

    // 遍历兄弟结点
    XMLElement* itemNode = doc.FirstChildElement()->FirstChildElement( "channel" )->FirstChildElement( "item" ); 
    while(itemNode != nullptr)
    {
        XMLElement* titleNode = itemNode->FirstChildElement( "title" );
        XMLElement* linkNode = itemNode->FirstChildElement( "link" );
        XMLElement* descriptionNode = itemNode->FirstChildElement( "description" );
        XMLElement* contentNode = itemNode->FirstChildElement( "content:encoded" );

        RssItem ri = {titleNode->GetText(), linkNode->GetText(), descriptionNode->GetText(), contentNode->GetText()};
        reader._res.push_back(ri);
        itemNode = itemNode->NextSiblingElement();//下一个兄弟节点
    }

    for(const auto & ri : reader._res)
    {
        cout << "title = " << ri.title <<endl;
        cout << "link = " << ri.link <<endl;
        cout << "description = " << ri.description <<endl;
        cout << "content = " << ri.content <<endl;
    }

}

int main(int argc, char* argv[])
{
    example_4();
    return 0;
}

