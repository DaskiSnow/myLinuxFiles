#include <func.h>

void delDir(const char* src);

int main(int argc, char* argv[])
{
    // ./delDir dirpath
    ARGS_CHECK(argc, 2);
    delDir(argv[1]);
    return 0;
}

void delDir(const char* src) {
    DIR* pdir = opendir()
}

