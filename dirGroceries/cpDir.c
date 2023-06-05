#include <func.h>

void cpFile(const char* src, const char* dst);
void cpDir(const char* src, const char* dst);

int main(int argc, char* argv[])
{
    // ./cpDir src dst
    ARGS_CHECK(argc, 3);
    cpDir(argv[1], argv[2]);
    return 0;
}

void cpDir(const char* src, const char* dst) {
    // ./cpDir dir

    // 打开源目录 
    DIR* pdir = opendir(src);
    ERROR_CHECK(pdir, NULL, "opendir");

    // 若dst目录不存在，创建dst目录
    if(access(dst, F_OK) == -1){ 
        errno = 0; // 重置errno, 避免影响其他的ERROR_CHECK
        // 获取目录权限信息
        struct stat dir_stat;
        int ret_stat = stat(src, &dir_stat);
        ERROR_CHECK(ret_stat, -1, "stat");

        // 新建一个目标地址的目录
        int ret_mkdir = mkdir(dst,dir_stat.st_mode);
        ERROR_CHECK(ret_mkdir, -1, "mkdir");
    }

    // 遍历目录项
    while(1) {
        struct dirent* pdirent = readdir(pdir);
        if(errno) perror("readdir");
        if(pdirent == NULL) break;

        // 忽略.和..开头的文件
        if(pdirent->d_name[0] == '.') continue;

        // 拼接文件或目录路径
        char src_subpath[128] = {0};
        char dst_subpath[128] = {0};
        sprintf(src_subpath, "%s/%s", src, pdirent->d_name);
        sprintf(dst_subpath, "%s/%s", dst, pdirent->d_name);

        // 如果文件类型为目录
        if(pdirent->d_type == DT_DIR) {
            cpDir(src_subpath, dst_subpath);
        }
        else{ // 其他类型的文件
            cpFile(src_subpath, dst_subpath);
        }
    }
    // 关闭！
    closedir(pdir);
}

void cpFile(const char* src, const char* dst) {
    int fdr = open(src, O_RDONLY);
    ERROR_CHECK(fdr, -1, "fdr");

    // 获取文件权限信息
    struct stat buf_stat;
    int ret_stat = stat(src, &buf_stat);
    ERROR_CHECK(ret_stat, -1, "stat");

    // 新建复制文件，并复制文件权限信息
    int fdw = open(dst, O_WRONLY | O_TRUNC | O_CREAT, buf_stat.st_mode);
    if(fdw == -1) {
        perror("fdw");
        close(fdr);
        exit(1);
    }

    // 复制文件内容
    while(1) {
        char buf[4096];
        int rret, wret;
        rret = read(fdr, buf, sizeof(buf));
        ERROR_CHECK(fdr, -1, "read");
        if(rret == 0) break;
        wret = write(fdw, buf, rret);
        ERROR_CHECK(wret, -1, "write");
    }

    //关闭！
    close(fdw);
    close(fdr);
}
