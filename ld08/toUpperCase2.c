#include <func.h>

void to_upper_space(char buf[], int n);

int main(int argc, char* argv[])
{
    // ./toUpperCase file_path

    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    size_t len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char* p = (char*)mmap(NULL,len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    to_upper_space(p, len);

    munmap(p, len);
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
