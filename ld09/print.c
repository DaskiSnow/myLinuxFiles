#include <func.h>

int main(int argc, char* argv[])
{
    // ./print file 
    // 集中输出到一个文件中
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0664);
    printf("\n");  // 防BUG
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    printf("Hello\n");
    fprintf(stderr, "World\n");

    close(fd);
    return 0;
}

