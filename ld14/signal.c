#include <func.h>

void handler(int signum) {
    printf("signum = %d\n",signum);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    while(1);
    return 0;
}

