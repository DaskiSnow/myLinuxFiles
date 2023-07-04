#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

// 用于存储待检测的字符串
class StrStorage {
public:
    StrStorage(const string & str)
    : _curr(0)
    , _str(string(str))
    {}

    // 查看_curr+1所指的字符
    char peek() {
        return _str.at(_curr + 1);
    }

    // 获取_curr所指的字符
    char curr() {
        return _str.at(_curr);
    }

    // 返回当前所指字符，并前进一个单位
    char advance() {
        if(isEnd()) return _str.at(_curr - 1);
        return _str.at(_curr++);
    }

    // 获取_curr - 1所指的字符
    char back() {
        return _str.at(_curr - 1);
    }

    bool isEnd() {
        return _curr == _str.length();
    }

private:
    int _curr; // 待检测字符的索引
    string _str;
};

bool isNum(string str) {
    StrStorage ts(str); // testing string
    
    // 有限状态机
    if(ts.curr() == '+' || ts.curr() == '-' || isdigit(ts.curr())) {
        ts.advance();
        if(isdigit(ts.curr())) {
            ts.advance();
            while(!ts.isEnd() && isdigit(ts.curr())) {
                ts.advance();
            }
            if(ts.isEnd()) {
                return true;
            }
            else if(ts.curr() == '.') {
                ts.advance();
                if(isdigit(ts.curr())) {
                    ts.advance();
                    while(!ts.isEnd() && isdigit(ts.curr())) {
                        ts.advance();
                    }
                    if(ts.isEnd()) {
                        return true;
                    }
                    else if(ts.curr() == 'e' || ts.curr() == 'E') {
                        ts.advance();
                        if(ts.curr() == '+' || ts.curr() == '-' || isdigit(ts.curr())) {
                            ts.advance();
                            if(isdigit(ts.back()) && ts.isEnd()) {
                                return true;
                            }
                            if(isdigit(ts.curr())) {
                                ts.advance();
                                while(!ts.isEnd() && isdigit(ts.curr())) {
                                    ts.advance();
                                }
                                if(ts.isEnd()) {
                                    return true;
                                }
                                else {
                                    return false;
                                }
                            }
                            
                        }
                        else {
                            return false;
                        }
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }
            else if(ts.curr() == 'e' || ts.curr() == 'E') {
                ts.advance();
                if(ts.isEnd()) return false;
                if(ts.curr() == '+' || ts.curr() == '-' || isdigit(ts.curr())) {
                    ts.advance();
                    if(isdigit(ts.back()) && ts.isEnd()) {
                        return true;
                    }
                    if(isdigit(ts.curr())) {
                        ts.advance();
                        while(!ts.isEnd() && isdigit(ts.curr())) {
                            ts.advance();
                        }
                        if(ts.isEnd()) {
                            return true;
                        }
                        else {
                            return false;
                        }
                    }
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else if(ts.curr() == 'e' || ts.curr() == 'E') {
            ts.advance();
            if(ts.isEnd()) return false;
            if(ts.curr() == '+' || ts.curr() == '-' || isdigit(ts.curr())) {
                ts.advance();
                if(isdigit(ts.back()) && ts.isEnd()) {
                    return true;
                }
                if(isdigit(ts.curr())) {
                    ts.advance();
                    while(!ts.isEnd() && isdigit(ts.curr())) {
                        ts.advance();
                    }
                    if(ts.isEnd()) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
            }
            else {
                return false;
            }
        }
        else if(ts.curr() == '.') {
            ts.advance();
            if(isdigit(ts.curr())) {
                ts.advance();
                while(!ts.isEnd() && isdigit(ts.curr())) {
                    ts.advance();
                }
                if(ts.isEnd()) {
                    return true;
                }
                else if(ts.curr() == 'e' || ts.curr() == 'E') {
                    ts.advance();
                    if(ts.curr() == '+' || ts.curr() == '-' || isdigit(ts.curr())) {
                        ts.advance();
                        if(isdigit(ts.back()) && ts.isEnd()) {
                            return true;
                        }
                        if(isdigit(ts.curr())) {
                            ts.advance();
                            while(!ts.isEnd() && isdigit(ts.curr())) {
                                ts.advance();
                            }
                            if(ts.isEnd()) {
                                return true;
                            }
                            else {
                                return false;
                            }
                        }

                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

int main(int argc, char* argv[])
{
    string str;
    cin >> str;
    cout << str << endl;
    cout << "isNum(str) = " << isNum(str) << endl;

    return 0;
}

