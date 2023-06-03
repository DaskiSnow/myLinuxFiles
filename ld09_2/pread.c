#include <func.h>

int main(int argc, char* argv[])
{
    // pread pipe
    ARGS_CHECK(argc, 2);
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open fdr");
    printf("fdr = %d\n", fdr);
    char buf[128] = {0};
    read(fdr, buf, sizeof(buf));
    printf("buf = %s\n",buf);

    return 0;
}

