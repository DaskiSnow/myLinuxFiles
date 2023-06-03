#include <func.h>

// 创建一个文件，里面有100万个字符'1'
int main(void)
{
    int fd = open("many_1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    ERROR_CHECK(fd, -1, "open");

    char str[100000];
    memset(str, '1', sizeof(str));
    for(int i = 0; i < 10 ;i++) {
        int wret = write(fd, str, sizeof(str));
//        printf("wret = %d\n", wret);
    }

    close(fd);
    return 0;
}

