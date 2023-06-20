#include <func.h>
int main(int argc, char *argv[]){
    int ret = chdir("~/Me");
    ERROR_CHECK(ret, -1, "chdir");
    return 0;
}

