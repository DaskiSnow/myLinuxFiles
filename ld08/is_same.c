#include <func.h>

// 判断任意两个文件的内容是否完全一致
int main(int argc, char* argv[])
{
    // ./is_same file1 file2

    // 打开两个文件
    ARGS_CHECK(argc, 3);

    int fd1 = open(argv[1], O_RDONLY);
    ERROR_CHECK(fd1, -1, "open src");

    int fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1) {
        perror("open dst");
        close(fd1);
        exit(1);
    }

    char src_buf[4096] = "";
    char dst_buf[4096] = "";
    while(1) {
        // 分别读取进两个用户态缓冲区
        ssize_t src_rret = read(fd1, src_buf, sizeof(src_buf));
        ERROR_CHECK(src_rret, -1, "read src");
        ssize_t dst_rret = read(fd2, dst_buf, sizeof(dst_buf));
        ERROR_CHECK(dst_rret, -1, "dst src");
        
        // 比较长度
        if (src_rret != dst_rret) {
            puts("false");
            return 0;
        }

        // 判断 是否已经读到文件末尾
        if(src_rret == 0) break;

        // 比较缓冲区
        int cmp_ret = memcmp(src_buf, dst_buf, sizeof(src_buf));
        if (cmp_ret){
            puts("false");
            return 0;
        }

    } // src_rret == 0

    puts("true");

    close(fd2);
    close(fd1);
    return 0;
}

