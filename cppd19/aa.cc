#include <iostream>
#include <string>
#include <typeinfo>
#include <map>
#include <utility>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;
using std::pair;

int main(int argc, char* argv[])
{
    const std::initializer_list<pair<string, int>> il = {{"AA",1}, {"BB", 2}}; 
    map<string, int> strmap(il.begin(), il.end());
    for( const auto & p : strmap )
    {
        cout << p.first << ","<< p.second <<endl;
    }
    return 0;
}

