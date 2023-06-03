#include <func.h>

typedef struct meta_info_s{
    char file_name[1024];
    int length;
}meta_info_t;

int main(int argc, char* argv[])
{
    // ./homework_3_A 1.pipe src_file_path
    ARGS_CHECK(argc, 3);
    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open fdw");
    int fdr = open(argv[2], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open fdr");

    // 准备元信息
    struct stat meta_stat;
    meta_info_t meta_info;
    int ret_fstat = fstat(fdr, &meta_stat);
    ERROR_CHECK(ret_fstat, -1, "fstat");
    strcpy(meta_info.file_name, argv[2]);
    meta_info.length = meta_stat.st_size;

    // 发送元信息
    int wret = write(fdw, &meta_info, sizeof(meta_info));
    ERROR_CHECK(wret, -1, "write meta");

    // 发送文件内容
    char buf[4096];
    int n;
    while(1) {
        n = read(fdr, buf, sizeof(buf));
        ERROR_CHECK(n, -1, "read content");
        if (n == 0) break;
        wret = write(fdw, buf, n);
        ERROR_CHECK(wret, -1, "write content");
    }

    // 发送完毕
    printf("Send over! File: %s, Size: %d\n", meta_info.file_name, meta_info.length);
    close(fdr);
    close(fdw);

    return 0;
}

