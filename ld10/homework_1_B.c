#include <func.h>

int main(int argc, char* argv[])
{
    // ./homework_1_B 1.pipe
    ARGS_CHECK(argc, 2);
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open fdr");

    char buf[1024] = {0};
    // 读取管道数据,并输出到标准输出
    read(fdr, buf, sizeof(buf));
    printf("%s\n", buf);

    return 0;
}

