#include <func.h>

typedef struct meta_info_s{
    char file_name[1024];
    int length;
}meta_info_t;

int main(int argc, char* argv[])
{
    // ./homework_3_B 1.pipe dst_dir
    ARGS_CHECK(argc, 3);
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open fdr");

    // 创建初始化栈变量，用于接收元信息
    meta_info_t meta_info;
    memset(meta_info.file_name, 0, sizeof(meta_info.file_name));
    meta_info.length = 0;
    
    // 接收元信息
    int rret;
    rret = read(fdr, &meta_info, sizeof(meta_info));
    ERROR_CHECK(rret, -1, "read meta_info");

    // 新建目录,新建文件
    int ret_mkdir = mkdir(argv[2], 0775);
    ERROR_CHECK(ret_mkdir, -1, "mkdir");
    int ret_chdir = chdir(argv[2]); // 改变当前工作目录
    ERROR_CHECK(ret_chdir, -1, "chdir");
    int fdw = open(meta_info.file_name, O_WRONLY | O_TRUNC | O_CREAT, 0666);
    ERROR_CHECK(fdw, -1, "open fdw");

    // 开始接收文件内容
    char buf[4096];
    int n;
    while(1){
        n = read(fdr, buf, sizeof(buf));
        ERROR_CHECK(n, -1, "read content");
        if(n == 0) break;
        int wret = write(fdw, buf, n);
        ERROR_CHECK(wret, -1, "write content");
    }

    close(fdw);
    close(fdr);
    printf("Receive over! File: %s, Size: %d\n", meta_info.file_name, meta_info.length);
    return 0;
}

