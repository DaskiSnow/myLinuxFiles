#include <func.h>

void handler(int signum) {
    printf("Before signum = %d\n",signum);
    sleep(5);
    printf("After signum = %d\n",signum);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, handler); // signum = 2
    signal(SIGQUIT, handler); // signum = 3
    while(1);
    return 0;
}

