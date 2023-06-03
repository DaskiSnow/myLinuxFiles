#include <func.h>

void copyFile(const char* src, const char* dst);
void copyDir(const char* src, const char* dst);

int main(int argc, char* argv[]) {
    // ./copyDir.c src dst，dts应为一个不存在的目录
    ARGS_CHECK(argc, 3);
    copyDir(argv[1], argv[2]);
    return 0;
}

void copyFile(const char* src, const char* dst) {
    // 复制文件
    FILE* fp_src = fopen(src, "rb");
    if (!fp_src) {
        fprintf(stderr, "Open %s failed\n", src);
        exit(1);
    }
    FILE* fp_dst = fopen(dst, "wb");
    if (!fp_dst) {
        fprintf(stderr, "Open %s failed\n", dst);
        fclose(fp_src);
        exit(1);
    }

    int n;
    char buffer[1024];
    while( (n = fread(buffer, 1, SIZE(buffer), fp_src)) > 0) {
        fwrite(buffer, 1, n, fp_dst);
    }

    fclose(fp_src);
    fclose(fp_dst);
}

void copyDir(const char* src, const char* dst) {
    // 创建dst目录
    int ret_mkdir = mkdir(dst, 0775); // 注意八进制数字面值的表示
    ERROR_CHECK(ret_mkdir, -1, "mkdir");
    
    // 打开src目录
    DIR* pdir = opendir(src);
    ERROR_CHECK(pdir, NULL, "opendir");
    
    // 遍历目录流
    errno = 0;
    struct dirent* pdirent;
    while((pdirent = readdir(pdir)) != NULL){
        // 忽略.和..
        char* name = pdirent->d_name;
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0){
            continue;
        }
        
        // 获取合并后的路径（文件夹名或文件名）
        char subsrc[1024];
        char subdst[1024];
        sprintf(subsrc, "%s/%s", src, name);
        sprintf(subdst, "%s/%s", dst, name);

        // 如果该目录项是文件，则调用copyFile复制文件
        if (pdirent->d_type == DT_REG) {
            copyFile(subsrc, subdst);
        }
        // 如果该目录项是目录，则调用copyDir递归复制
        if (pdirent->d_type == DT_DIR) {
            copyDir(subsrc, subdst);
        }
    }

    if (errno) {
        perror("readdir");
        exit(1);
    }

    // 关闭目录流
    closedir(pdir);
}
