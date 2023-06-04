#include <func.h>

void dfs_print(const char* path, int width);

int directories = 0, files = 0;

int main(int argc, char* argv[])
{
    // ./mytree dir
    ARGS_CHECK(argc, 2);

    puts(argv[1]);

    dfs_print(argv[1], 4);

    printf("%d directories, %d files\n", directories, files);

    return 0;
}

void dfs_print(const char* path, int width) {
    DIR* pdir = opendir(path);
    ERROR_CHECK(pdir, NULL, "open dir");

    // 遍历目录项
    struct dirent *pdirent;
    while(1) {
        pdirent = readdir(pdir);
        if(errno) {
            perror("readdir");
            exit(1);
        }
        if(pdirent == NULL) break;

        // 忽略开头为.和..文件
        if(pdirent->d_name[0] == '.') continue;

        // 打印目录项名字
        for(int i = 0; i < width; i++) printf(" ");
        printf("%s\n",pdirent->d_name);

        // 如果是文件类型为目录, dfs
        if(pdirent->d_type == DT_DIR) {
            directories++;
            char new_path[256] = {0};
            sprintf(new_path, "%s/%s", path, pdirent->d_name);
            dfs_print(new_path, width + 4);
        }
        else {
            files++;
        }
    }
    closedir(pdir);
    return;
}

