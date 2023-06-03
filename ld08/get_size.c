#include <func.h>

int main(int argc, char* argv[])
{
    // ./get_size file
    ARGS_CHECK(argc, 2);
    struct stat buf;
    int ret_stat = stat(argv[1], &buf);
    ERROR_CHECK(ret_stat, -1, "stat");
    printf("Size of %s: %d bytes\n", argv[1], buf.st_size);
    return 0;
}

