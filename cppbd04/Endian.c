#include <func.h>

int main(int argc, char* argv[])
{
    unsigned int num = 0x12345678;
    char *c = (char *)&num;
    if(*c == 0x78)
    {
        printf("Little Endian\n");
    }
    else if(*c == 0x12)
    {
        printf("Big Endian");
    }
    return 0;
}

