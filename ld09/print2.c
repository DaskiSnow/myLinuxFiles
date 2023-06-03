#include <func.h>

int main(int argc, char* argv[])
{
    // ./print2 file1 file2
    ARGS_CHECK(argc, 3);
    int fd_out = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0664);
    ERROR_CHECK(fd_out, -1, "open fd_out");
    int fd_err = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0664);
    ERROR_CHECK(fd_err, -1, "open fd_err");

    printf("\n"); // 避免BUG
    
    // 分别重定向stdout和stderr
    dup2(fd_out, STDOUT_FILENO);
    dup2(fd_err, STDERR_FILENO);

    // 写入
    printf("Hello\n");
    fprintf(stderr, "World\n");

    // 关闭文件对象
    close(fd_err);
    close(fd_out);

    return 0;
}

