#include <func.h>

void to_upper_space(char buf[], int n);

int main(int argc, char* argv[])
{
    // ./toUpperCase file_path

    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    char buf[4096]={'\0'};
    int n;
    // while ( (n = read(fd, buf, sizeof(buf))) > 0) {
    //     to_upper_space(buf, SIZE(buf));
    // }
    while (1) {
        n = read(fd, buf, sizeof(buf));
        if (n <= 0) break;
        to_upper_space(buf, SIZE(buf));
        lseek(fd, -n, SEEK_CUR);
        write(fd, buf, n);
        lseek(fd, n, SEEK_CUR);
    }
    if(errno){
        perror("read");
        close(fd);
        exit(1);
    }

    close(fd);
    return 0;
}

void to_upper_space(char buf[], int n) {
    for(int i = 0; i < n; i++) {
        if (ispunct(buf[i])){
            buf[i] = ' ';
        }
        else{
            buf[i] = toupper(buf[i]);
        }
    }
}
