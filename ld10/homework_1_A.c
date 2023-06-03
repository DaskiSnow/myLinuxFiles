#include <func.h>

int main(int argc, char* argv[])
{
    // ./homework_1_A.c 1.pipe
    ARGS_CHECK(argc, 2);
    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open fdw");

    char buf[1024] = "Helloworld\n";
    // 显示在A的标准输出
    printf("%s",buf);

    // 显示在B的标准输出
    int fd_backup = dup(STDOUT_FILENO);
    dup2(fdw, STDOUT_FILENO);
    printf("%s",buf);
    // 显示在A的标准输出
    dup2(fd_backup, STDOUT_FILENO);
    printf("%s", buf);

    return 0;
}

