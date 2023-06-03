#include <func.h>

typedef struct student_s{
    int num;
    char name[128];
    float score;
}student_t;

int main(void)
{
    student_t s1[3] = {
        {1,"XiaoMing",89},
        {2,"XiaoZhang",98},
        {3,"XiaoLi",80}
    };

    int fd = open("lseek_test", O_RDWR | O_CREAT | O_TRUNC, 0664);
    ERROR_CHECK(fd, -1, "open");
    ssize_t sret = write(fd, s1, sizeof(s1));
    ERROR_CHECK(sret, -1, "write");
    // lseek到开头，读取内容并printf输出
    off_t lret = lseek(fd, 0, SEEK_SET);
    student_t s2[3];
    ssize_t rret = read(fd, s2, sizeof(s2));
    ERROR_CHECK(rret, -1, "read");
    for(int i = 0; i < 3; i++) {
        printf("%d %s %f\n", s2[i].num, s2[i].name, s2[i].score);
    }
    close(fd);
    return 0;
}

