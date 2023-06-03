#include <func.h>

void deleteDir(const char* path);

int main(int argc, char* argv[])
{
    // ./deleteDir dir
    ARGS_CHECK(argc, 2);

    deleteDir(argv[1]);

    return 0;
}

void deleteDir(const char* path) {
    // 打开目录
    DIR* pdir = opendir(path);
    ERROR_CHECK(pdir, NULL, "opendir");

    // 遍历目录流，依次删除每一个目录项
    errno = 0;
    struct dirent* pdirent;
    while((pdirent = readdir(pdir)) != NULL) {
        // 忽略.和..
        char* name = pdirent->d_name;
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            continue;
        }

        // 合成路径，获得文件名或文件夹名
        char subpath[1024];
        sprintf(subpath, "%s/%s", path, name);

        // 如果该目录项是文件，则调用unlink删除文件
        if (pdirent->d_type == DT_REG) {
            unlink(subpath);
        }
        // 如果该目录项是目录，则调用deleteDir递归删除
        if (pdirent->d_type == DT_DIR) {
            deleteDir(subpath);
        }
    }
    
    // 目录为空，可以删除目录
    rmdir(path);

    // 关闭目录流
    closedir(pdir);
}
