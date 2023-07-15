#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::istringstream;
using std::ostringstream;

int main(int argc, char* argv[])
{
    istringstream iss(string("ABC EFO"));
    string input_str;
    iss >> input_str;
    cout << input_str << endl;
    iss >> input_str;
    cout << input_str << endl;
    cout << iss.eof() << endl;

    return 0;
}

