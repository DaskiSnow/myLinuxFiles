#include "5_String.hh"
#include <string.h>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::cerr;

String::String()
: _pstr(new char[1]())
{
    _pstr[0] = '\0';
}

String::String(const char * str) 
{
    if(!str) {
        _pstr = new char[1]();
        _pstr[0] = '\0';
    }
    _pstr = new char[strlen(str) + 1]();
    strcpy(_pstr, str); 
}

String::String(const String & str) 
{
    _pstr = new char[strlen(str._pstr) + 1]();
    strcpy(_pstr, str._pstr); 
}

String::~String() {
    if(_pstr) {
        delete [] _pstr;
        _pstr = nullptr;
    }
}

String &String::operator=(const String & str) 
{
    if(this == &str) return *this;
    delete [] _pstr;
    _pstr = new char[strlen(str._pstr) + 1]();
    strcpy(_pstr, str._pstr); 
    return *this;
}

String &String::operator=(const char * str) 
{
    delete [] _pstr;
    _pstr = new char[strlen(str) + 1]();
    strcpy(_pstr, str); 
    return *this;
}


String &String::operator+=(const String & str)
{
    char* temp_pstr = new char[strlen(_pstr) + strlen(str._pstr) + 1]();
    strcpy(temp_pstr, _pstr);
    strcat(temp_pstr, str._pstr);
    delete [] _pstr;
    _pstr = temp_pstr;
    return *this;
}

String &String::operator+=(const char * str)
{
    char* temp_pstr = new char[strlen(_pstr) + strlen(str) + 1]();
    strcpy(temp_pstr, _pstr);
    strcat(temp_pstr, str);
    delete [] _pstr;
    _pstr = temp_pstr;
    return *this;
}


char &String::operator[](std::size_t index)
{
    if(index > strlen(_pstr)) {
        /* cerr << "invalid index" << endl; */
        return _pstr[strlen(_pstr)];
    }
    return _pstr[index];
}

const char &String::operator[](std::size_t index) const
{
    if(index > strlen(_pstr)) {
        /* cerr << "invalid index" << endl; */
        return _pstr[strlen(_pstr)];
    }
    return _pstr[index];
}


std::size_t String::size() const
{
    return strlen(_pstr);
}

const char* String::c_str() const
{
    return _pstr;
}


bool operator==(const String & str1, const String & str2) 
{
    if(strcmp(str1._pstr, str2._pstr) == 0) return true;
    return false;
}

bool operator!=(const String & str1, const String & str2) 
{
    if(strcmp(str1._pstr, str2._pstr) != 0) return true;
    return false;
}


bool operator<(const String & str1, const String & str2) 
{
    if(strcmp(str1._pstr, str2._pstr) < 0) return true;
    return false;
}

bool operator>(const String & str1, const String & str2) 
{
    if(strcmp(str1._pstr, str2._pstr) > 0) return true;
    return false;
}

bool operator<=(const String & str1, const String & str2) 
{
    if(strcmp(str1._pstr, str2._pstr) > 0) return false;
    return true;
}

bool operator>=(const String & str1, const String & str2) 
{
    if(strcmp(str1._pstr, str2._pstr) < 0) return false;
    return true;
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
   os << s._pstr; 
   return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
    is >> s._pstr;
    return is;
}

String operator+(const String & str1, const String & str2) 
{
    char* temp_pstr = new char[strlen(str1.c_str()) + strlen(str2.c_str()) + 1]();
    strcpy(temp_pstr, str1.c_str());
    strcat(temp_pstr, str2.c_str());

    String ret_str(temp_pstr);
    
    delete [] temp_pstr;

    return ret_str;
}

String operator+(const String & str1, const char * str2)
{
    char* temp_pstr = new char[strlen(str1.c_str()) + strlen(str2) + 1]();
    strcpy(temp_pstr, str1.c_str());
    strcat(temp_pstr, str2);

    String ret_str(temp_pstr);
    
    delete [] temp_pstr;

    return ret_str;
}

String operator+(const char * str1, const String & str2)
{
    char* temp_pstr = new char[strlen(str1) + strlen(str2.c_str()) + 1]();
    strcpy(temp_pstr, str1);
    strcat(temp_pstr, str2.c_str());

    String ret_str(temp_pstr);
    
    delete [] temp_pstr;

    return ret_str;
}

int main(int argc, char* argv[])
{
    String s1;
    cout << "String s1, s1 = "<<s1 << endl << endl;

    String s2("abc");
    cout << "String s2(\"abc\"), s2 = " << s2 << endl << endl;

    String s3(s2);
    cout << "String s3(s2), s3 = " << s3 << endl << endl;

    String s4("opq");
    s2 = s4;
    cout << "String s4(\"opq\")  s2 = s4, s2 = " << s2 << endl << endl;

    String s5 = "rst";
    cout << "String s5 = \"rst\", s5 = " << s5 << endl << endl;

    s5+=s4;
    cout << "s5+=s4, s5 = " << s5 << endl << endl;
    
    s5+="uvw";
    cout << "s5+=\"uvw\", s5 = " << s5 << endl << endl;

    cout << "s5[2] = " << s5[2] << endl << endl;

    const String s6 = s5;
    cout << "const String s6 = s5  s6[3] = " << s6[3] << endl << endl;

    cout << "s5.size() = " << s5.size() << endl << endl;

    cout << "s5.c_str() =  " << s5.c_str() << endl << endl;

    cout << "s5 == s4, " << (s5 == s4) << endl;
    cout << "s5 == s6, " << (s5 == s6) << endl << endl;

    cout << "s5 != s4, " << (s5 != s4) << endl;
    cout << "s5 != s6, " << (s5 != s6) << endl << endl;

    cout << "s5 > s4, " << (s5 > s4) << endl;
    cout << "s5 > s6, " << (s5 > s6) << endl << endl;

    cout << "s5 < s4, " << (s5 < s4) << endl;
    cout << "s5 < s6, " << (s5 < s6) << endl << endl;

    cout << "s5 <= s4, " << (s5 <= s4) << endl;
    cout << "s5 <= s6, " << (s5 <= s6) << endl << endl;

    cout << "s5 >= s4, " << (s5 >= s4) << endl;
    cout << "s5 >= s6, " << (s5 >= s6) << endl << endl;

    cout << "cout << s6, " << s6 << endl << endl;

    cout << "pls input str:";
    String s7;
    cin >> s7;
    cout << "cin >> s7, s7 = " << s7 << endl << endl;

    cout << "s6 + s7 = " << s6 + s7 << endl << endl;

    cout << "s6 + \"QAQ\" = " << s6 + "QAQ" << endl << endl;

    cout << "\"TAT\" + s6 = " << "TAT" + s6 << endl << endl;
    
    return 0;
}

