#include <func.h>

void dfs_print(const char* path, int width); // width: 缩进的空格数目

int directories = 0, files = 0;

int main(int argc, char* argv[]){
    // ./tree dir
    ARGS_CHECK(argc, 2);

    puts(argv[1]); // 打印目录的名字

    dfs_print(argv[1], 4); // 递归打印每一个目录项

    printf("\n%d directories, %d files\n",directories, files); // 最后打印统计信息

    return 0;
}

void dfs_print(const char* path, int width){
    DIR* pdir = opendir(path);
#ifdef DEBUG
        printf("path = %s\n", path);
#endif
    ERROR_CHECK(pdir, NULL, "opendir");

    struct dirent* pdirent;
    errno = 0;
    while((pdirent = readdir(pdir)) != NULL) {
        const char* name = pdirent->d_name;
#ifdef DEBUG
        printf("name = %s\n", name);
#endif
        if (name[0] == '.') continue;
        for(int i = 0; i < width; i++){
            printf(" ");
        }
        printf("%s\n", name);

        if (pdirent->d_type == DT_DIR) { // 目录项类型为目录
            directories++;

            char subpath[1024];
            sprintf(subpath,"%s/%s",path,name);
            dfs_print(subpath, width+4); 
        }
        else{
            files++;
        }
    }

    if (errno) {
        perror("dfs_print");
        exit(1);
    }
    closedir(pdir);
}

