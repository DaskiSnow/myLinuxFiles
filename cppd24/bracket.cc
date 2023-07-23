#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution {
    friend void test();
public:
    bool isValid(string s) 
    {
        for(const auto & ch : s)
        {
            if(ch == '(' || ch == '[' || ch == '{') {
                _stack.push(ch);
                continue;
            }
            else
            {
                if(_stack.empty())
                {
                    return false;
                }
                if(_stack.top() == '(' && ch == ')')
                {
                    _stack.pop();
                }
                else if(_stack.top() == '[' && ch == ']') 
                {
                    _stack.pop();
                }
                else if(_stack.top() == '{' && ch == '}')
                {
                    _stack.pop();
                }
                else 
                {
                    return false;
                }
            }
        }
        if(!_stack.empty())
        {
            return false;
        }
        return true;
    }
private:
    stack<char> _stack;    
};

void test()
{
    string str = "(";
    Solution s;
    cout << s.isValid(str) << endl;
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

