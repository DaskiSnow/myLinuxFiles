#include <iostream>
#include <string>
#include <regex>
using std::cout;
using std::cin;
using std::endl;
using std::string;

void test()
{
    std::string str = "wowowo<p>hahaha";
    std::regex reg("<p>");
    std::smatch match;

    if (std::regex_search(str, match, reg)) {
        std::cout << "Match found at position " << match.position() << std::endl;
        std::cout << "Matched string: " << match.str() << std::endl;
    } else {
        std::cout << "No match found" << std::endl;
    }

}

void test2()
{
    std::string str = "wowowo<p>hahaha";
    std::regex reg("<.*>");
    std::string replacement = "";
    std::string new_str = std::regex_replace(str, reg, replacement);

    std::cout << "Original string: " << str << std::endl;
    std::cout << "New string: " << new_str << std::endl;
}

int main(int argc, char* argv[])
{
    test2();

}

