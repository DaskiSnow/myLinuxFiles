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

bool example_4()
{
    static const char* xml =
        "<information>"
        "   <attributeApproach v='2' />"
        "   <textApproach>"
        "       <v>2</v>"
        "   </textApproach>"
        "</information>";

    int v0, v1;

    XMLDocument doc;
    doc.LoadFile("resources/dream.xml");
    XMLElement* itemElement = doc.FirstChildElement()->FirstChildElement( "channel" )->FirstChildElement( "item" );

    // 遍历兄弟结点
    XMLElement* itemNode = doc.FirstChildElement()->FirstChildElement( "channel" )->FirstChildElement( "item" ); 
    while(itemNode != nullptr)
    {
        // XMLElement* 
        itemNode = itemNode->NextSiblingElement();//下一个兄弟节点
    }
    // attributeApproachElement->QueryIntAttribute( "v", &v0 );

    XMLElement* textApproachElement = doc.FirstChildElement()->FirstChildElement( "textApproach" );
    textApproachElement->FirstChildElement( "v" )->QueryIntText( &v1 );

    cout << "v0 = " << v0 << endl;
    cout << "v0 = " << v1 << endl;

}

bool myExample_4()
{

}

int main(int argc, char* argv[])
{
    example_3();
    return 0;
}

