#include <func.hh>
#include <crypt.h>

using namespace std;

const int SALTSIZE = 8;

string pool = "0123456789qwertyuiopasdfghjklzxcvbnm";
int poolSize = pool.size();

string encode(const string &passwd) {
        srand(time(nullptr));
        string salt = "";
        for (int i = 0; i < SALTSIZE; ++i) 
        {
                int rands = rand() % poolSize;
                salt += pool[rands];
        }
        string encodedPasswd(crypt(passwd.c_str(), salt.c_str()));
        return "$" + salt + "$" + encodedPasswd;
}

int main(int argc, char *argv[])
{
    cout << encode("ascv") << endl;;    
    return 0;
}

