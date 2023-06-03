// chdir.c
#include <func.h>

// ./chdir dir
int main(int argc, char *argv[]) {
    ARGS_CHECK(argc, 2);

    char buf[256];
    getcwd(buf, SIZE(buf));
    puts(buf);

    int ret = chdir(argv[1]);  // 改变当前工作目录
    ERROR_CHECK(ret, -1, "chdir");

    getcwd(buf, SIZE(buf));
    puts(buf);  // 打印当前目录
    
    return 0;
}
