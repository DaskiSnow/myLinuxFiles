#include <func.h>

int main(int argc, char* argv[])
{
    // ./pwrite pipe
    ARGS_CHECK(argc, 2);
    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open fdw");
    printf("fdw = %d\n",fdw);
    char buf[128] = "Hello two dimension\n";
    write(fdw, buf, strlen(buf));
    printf("buf = %s\n", buf);

    return 0;
}

